void setup() 
{
    pinMode(5, OUTPUT);
    pinMode(6, OUTPUT);
}

void loop() 
{
    digitalWrite(5, HIGH);
    digitalWrite(6, LOW);
    delay(5000);

}
