#include <DHT.h>  
#include <ESP8266WiFi.h>  
#include <WiFiClient.h>  
#include <ThingSpeak.h>
  
#define DHTPIN D2
#define DHTTYPE DHT22  

DHT dht(DHTPIN, DHTTYPE);  

const char* ssid = "Advance Tech 2";  
const char* password = "advance@20";  

WiFiClient client;  

unsigned long myChannelNumber = 518558;  
const char * myWriteAPIKey = "7J722QQJY3F8X2I8";  
float temperature, humidity;  
void setup()  
{  
  Serial.begin(115200);  
  dht.begin();  
  delay(10);  
  // Connect to WiFi network  
  Serial.println();  
  Serial.println();  
  Serial.print("Connecting to ");  
  Serial.println(ssid);  
  WiFi.begin(ssid, password);  
  while (WiFi.status() != WL_CONNECTED)  
  {  
   delay(500);  
   Serial.print(".");  
  }  
  Serial.println("");  
  Serial.println("WiFi connected");  
  // Print the IP address  
  Serial.println(WiFi.localIP());  
  ThingSpeak.begin(client);  
}  
void loop()   
{
  float converted = 0.00;
  temperature = dht.readTemperature();  
  humidity = dht.readHumidity();  
  Serial.print("Temperature Value is :");  
  Serial.print(temperature);  
  Serial.println("C");  
  Serial.print("Humidity Value is :");  
  Serial.print(humidity);  
  Serial.println("%");   
  ThingSpeak.writeField(myChannelNumber, 1, temperature, myWriteAPIKey);  
  ThingSpeak.writeField(myChannelNumber, 2, humidity, myWriteAPIKey);  
  delay(30000); // ThingSpeak will only accept updates every 15 seconds.
}  
