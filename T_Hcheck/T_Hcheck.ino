#include <dht.h>

dht DHT;

#define DHT11_PIN 2

void setup(){
  Serial.begin(9600);
}

void loop()
{
  int check = DHT.read11(DHT11_PIN);
  
  Serial.print("Temperature = ");
  Serial.println(DHT.temperature,1);
  Serial.print("Humidity = ");
  Serial.println(DHT.humidity,1);
  delay(1000);
}

