#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>

SoftwareSerial UNO (D2, D3);

                                    
void setup (void)
{
  Serial.begin(9600);
  UNO.begin(9600);
  pinMode(D2, INPUT);
  pinMode(D3, OUTPUT);

}  

void loop (void)
{
   while(UNO.available()){
    char val = UNO.read();
    Serial.print(val);
 }
  delay(50);
} 
