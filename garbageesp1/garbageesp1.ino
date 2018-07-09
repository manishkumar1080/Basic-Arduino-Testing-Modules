#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
                                
void setup ()
{
  Serial.begin(9600);
  pinMode(D2, INPUT);
  pinMode(D3, OUTPUT);

}  

void loop ()
{
   while(Serial.available()>0){
    if (Serial.read())
    {
      Serial.println(Serial.read());
      Serial.print('\n');
      delay(50);
    }
    }
    delay(50);
   }
