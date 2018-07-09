#define NUM_SAMPLES 10
                    
unsigned char sample_count = 0;
float voltage = 0.0;           

void setup()
{
    Serial.begin(9600);
}

void loop()
{
   int sensorValue=analogRead(A2);
   Serial.println(sensorValue);
   delay(10);
}
