#include <DHT.h>
#include <ESP8266WiFi.h>


#define DHTPIN D0  
#define DHTTYPE DHT11  

DHT dht(DHTPIN, DHTTYPE);

uint8_t temperature, humidity;  

void setup(){
  Serial.begin(115200);  
  dht.begin();  
  delay(10); 
}

void loop()
{
 temperature = dht.readTemperature();  
  humidity = dht.readHumidity();  
  Serial.print("Temperature Value is :");  
  Serial.print(temperature);  
  Serial.println("C");  
  Serial.print("Humidity Value is :");  
  Serial.print(humidity);  
  Serial.println("%");  
  delay(1000);
}

