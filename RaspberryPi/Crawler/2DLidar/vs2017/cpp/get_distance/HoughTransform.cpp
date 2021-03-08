#include <vector>
#include <tuple>
#include <iostream>

using namespace std;

// Functions are arranged in the order of use

void ReduceData(vector<pair<int, int>> Raw, vector<pair<int, int>>& Reduced)
{
    // unit -> mm
    int Roughness = 1;
    int ScanRange = 180;
    int Datanum = ScanRange / Roughness;
    int width = 500;
    int lookahead = 1000;
    int validdeg = Roughness * (180 / 3.1415) * atanf(lookahead / (0.5 * width));
    int invalid = Datanum - 2 * validdeg;
    for (int i = 0;i < Raw.size();i++)
    {
        if (i < validdeg)
        {
            Reduced.emplace_back(Raw[i]);
        }
        else
        {
            if (i < validdeg + invalid)
            {
            }
            else
            {
                Reduced.emplace_back(Raw[i]);
            }
        }
    }
}

void Hough(vector<pair<int,int>> Rawdata, vector<pair<int, int>>& RhoTheta)
{
    int roughness = 5;
    int ScanRange = 180;
    int total = ScanRange / roughness;
    for (int i = 0;i < Rawdata.size();i++)
    {
        for (int j = 0;j < total;j++)
        {
            int result = Rawdata[i].first * cos(3.1415 * roughness * (j + 1) / ScanRange) + Rawdata[i].second * sin(3.1415 * roughness * (j + 1) / ScanRange);
            RhoTheta.emplace_back(result, roughness * (j + 1));
        }
    }
}


//gain:(0~100%)
void LPF(vector<pair<int, int>> Data, vector<pair<int, int>>& Filtered, int gain)
{
    for (int i = 0;i < Data.size();i++)
    {
        static float Lpfed = 0;
        static float preLpf = 0;
        Lpfed = int((100 - gain) * 0.01 * Data[i].second + gain * 0.01 * preLpf);
        preLpf = Lpfed;
        Filtered.emplace_back(Data[i].first, Lpfed);
    }
}

// do step sort & vote
void StepSort(vector<pair<int, int>> Data, vector<tuple<float, int, int>>& Filtered, int step)
{
    //Sorting
    int Num = Data.size();
    pair<int, int> tmp = { 0,0 };
    for (int i = 0; i < Num; i++)
    {
        for (int j = i + 1; j < Num; j++)
        {
            if (Data[i].first > Data[j].first) {
                tmp = Data[i];
                Data[i] = Data[j];
                Data[j] = tmp;
            }
        }
    }

    vector<int> save_rad;
    for (int i = Data[0].first;i < Data[Num - 1].first; i += step)
    {
        int count = 0;
        //vector<int> save_rad;
        for (int j = 0;j < Num;j++)
        {
            if (Data[j].first >= i && Data[j].first < i + step)
            {
                save_rad.emplace_back(Data[j].second);
                count++;
            }
            else
            {
                //  break;
            }
        }
        if (save_rad.empty() == 0)
        {
            Filtered.emplace_back(0.5 * (2 * i + step - 1), save_rad[save_rad.size() / 2], count);
            //ex) 1,2,3,4,5,6,7,8,9,7,4,2,1 -> step:3 -> (median,num),(2,5),(5,4),(8,4)
        }
        else
        {
            Filtered.emplace_back(0.5 * (2 * i + step - 1), 0, count);
            //ex) 1,2,3,4,5,6,7,8,9,7,4,2,1 -> step:3 -> (median,num),(2,5),(5,4),(8,4)
        }
        save_rad.clear();
    }
    // Exception handling : put dummy data in begin and end
    Filtered.emplace(Filtered.begin(), Data[0].first - 0.5 * step, Data[0].second, 0);
    Filtered.emplace(Filtered.end(), Data[Num - 1].first + 0.5 * step, Data[Num - 1].second, 0);
}

void DetectPeak(vector<tuple<float, int, int>> Filtered, vector < tuple<float, int, int>>& Vpeaks)
{
    int Line = 2;
    //Bibun Filtered -> DData
    vector<int> DData;
    float deltaR = 0;
    float deltaNum = 0;
    float D = 0;
    for (int i = 0;i < Filtered.size() - 1;i++)
    {
        deltaR = get<0>(Filtered[i + 1]) - get<0>(Filtered[i]);
        deltaNum = get<2>(Filtered[i + 1]) - get<2>(Filtered[i]);
        D = deltaNum / deltaR;
        DData.emplace_back(D);
    }

    // find boundary between dydx > 0 and dydx < 0
    int flag = 0;
    vector<int> peaks; // save the number of peaks
    for (int i = 0;i < Filtered.size() - 2;i++)
    {
        flag = DData[i] * DData[i + 1];
        if (flag >= 0)
        {
            if (DData[i] == 0 || DData[i + 1] == 0)
            {
                peaks.emplace_back(i + 1);
            }
        }
        else
        {
            peaks.emplace_back(i + 1);
        }
    }

    //remake vector using number of peaks
   // vector<tuple<float, int, int>> Vpeaks;
    int peaks_num = peaks.size();
    for (int i = 0; i < peaks_num;i++)
    {
        Vpeaks.emplace_back(Filtered[peaks[i]]);
    }

    // sorting
    tuple<float, int, int> tmp = { 0,0,0 };
    for (int i = 0; i < peaks_num; i++)
    {
        for (int j = i + 1; j < peaks_num; j++)
        {
            if (get<2>(Vpeaks[i]) * get<2>(Vpeaks[i]) < get<2>(Vpeaks[j]) * get<2>(Vpeaks[j]))
            {
                tmp = Vpeaks[i];
                Vpeaks[i] = Vpeaks[j];
                Vpeaks[j] = tmp;
            }
        }
    }

     vector<int> peak;
    //   Thinning out
    while (true)
    {
        int size = Vpeaks.size();
        if (size == Line)
        {
            break;
        }
        else
        {
            if (size > Line)
            {
                Vpeaks.pop_back();
            }
            else
            {
                Vpeaks.clear();
                break;
            }
        }
    }
}

//get Lateral error between two lines
void  getErr(vector < tuple<float, int, int>> Lines, float& LatErr, float& degHeadErr)
{
    float lat1 = 0;
    float lat2 = 0;
    lat1 = get<0>(Lines[0]);
    lat2 = get<0>(Lines[1]);
    LatErr = -(lat1 + lat2);
    float average = 0;
    float head1 = 0;
    float head2 = 0;
    float err1 = 0;
    float err2 = 0;
    head1 = (180 / 3.1415) * atanf(1 / tanf(get<1>(Lines[0]) * 3.1415 / 180));
    if (head1 < 0)
    {
        head1 += 180;
    }
    if (head1 > 90)
    {
        err1 = head1 - 180;
    }
    else
    {
        err1 = head1;
    }
    head2 = (180 / 3.1415) * atanf(1 / tanf(get<1>(Lines[1]) * 3.1415 / 180));
    if (head2 < 0)
    {
        head2 += 180;
    }
    if (head2 > 90)
    {
        err2 = head2 - 180;
    }
    else
    {
        err2 = head2;
    }
    average = 0.5 * (err1 + err2);
    cout << " LateralError : " << LatErr << endl;
    cout << " HeadingError : " << average << endl;
}

// for Debug
void PrintVector(vector<tuple<float, int, int>> vec)
{
    for (int i = 0;i < vec.size();i++)
    {
        cout << get<0>(vec[i]) << " , " << get<1>(vec[i]) << " , " << get<2>(vec[i]) << endl;
    }
}

void PrintVector(vector<pair< int, int>> vec)
{
    for (int i = 0;i < vec.size();i++)
    {
        cout << vec[i].first << " , " << vec[i].second << endl;
    }
}

void getLine(vector < tuple<float, int, int>> Lines)
{
    float katamuki_0 = 0;
    float katamuki_1 = 0;
    katamuki_0 = -1 / tanf((3.1415 / 180) * get<1>(Lines[0]));
    katamuki_1 = -1 / tanf((3.1415 / 180) * get<1>(Lines[1]));
    cout << "y = " << katamuki_0 << " x + " << get<0>(Lines[0]) << endl;
    cout << "y = " << katamuki_1 << " x + " << get<0>(Lines[1]) << endl;
}