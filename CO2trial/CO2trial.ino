#include <ESP8266WiFi.h>  
#include <WiFiClient.h>  

int smoke = A0;
int sensorThres = 500;

void setup() {
  Serial.begin(9600);
  pinMode(smoke, INPUT);
  
  
}

void loop() {
  int analogSensor = analogRead(smoke);

  Serial.print("Sensor's Value : ");
  Serial.println(analogSensor);
  delay(100);
}
