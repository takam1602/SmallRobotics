#pragma once
#include <vector>
#include <tuple>
#include <iostream>

using namespace std;

// RawData -> Reducing (in front of sensor)
void ReduceData(vector<pair<int, int>> Raw, vector<pair<int, int>>& Reduced);

// Houghtransform  : get candidate rho and theta
void Hough(vector<pair<int, int>> Rawdata, vector<pair<int, int>>& RhoTheta);

// Filtering : easy to choose rho and theta
void LPF(vector<pair<int, int>> Data, vector<pair<int, int>>& Filtered, int gain);
void StepSort(vector<pair<int, int>> Data, vector<tuple<float, int, int>>& Filtered, int step);

// Peak detction : 
void DetectPeak(vector<tuple<float, int, int>> Filtered, vector < tuple<float, int, int>>& Vpeaks);
// get lateral and heading err
void  getErr(vector < tuple<float, int, int>> Lines, float& LatErr, float& degHeadErr);

// for Debug
void PrintVector(vector<tuple<float, int, int>> vec);
void PrintVector(vector<pair< int, int>> vec);
void getLine(vector < tuple<float, int, int>> Lines);