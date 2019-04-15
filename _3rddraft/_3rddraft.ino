#include <SoftwareSerial.h>
#include <DHT.h>  
#include <ESP8266WiFi.h>  
#include <WiFiClient.h>  
#include <ThingSpeak.h> 

#define DHTPIN D1  
#define DHTTYPE DHT11  

SoftwareSerial UNO (D2, D3);

DHT dht(DHTPIN, DHTTYPE);  

const char* ssid = "Bonjour";  
const char* password = "MARVEL10";  

WiFiClient client; 
 
unsigned long myChannelNumber = 750666;  
const char * myWriteAPIKey = "1UW6Z0JXPOFXQKXK";  
uint8_t temperature, humidity;  

void setup()  
{  
  Serial.begin(115200);  
  UNO.begin(9600);
  dht.begin();  
  delay(10);  
  pinMode(D2, INPUT);
  pinMode(D3, OUTPUT); 
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
  static boolean data_state = false; 
  temperature = dht.readTemperature();  
  humidity = dht.readHumidity();
  float gas = analogRead(A0);
  float val = UNO.read();  
  Serial.print("Temperature Value is :");  
  Serial.print(temperature);  
  Serial.println("C");  
  Serial.print("Humidity Value is :");  
  Serial.print(humidity);  
  Serial.println("%");  
  Serial.print("Gas Value is :");  
  Serial.print(gas);  
  if (isnan(gas))
  {
    Serial.println("Failed to read from MQ-5 sensor!");
    return;
}
   while(UNO.available())
   {
    float val = UNO.read();
    Serial.print(val);
   }
   ThingSpeak.writeField(myChannelNumber, 1, temperature, myWriteAPIKey);
   ThingSpeak.writeField(myChannelNumber, 2, humidity, myWriteAPIKey);
   ThingSpeak.writeField(myChannelNumber, 3, gas, myWriteAPIKey);
   ThingSpeak.writeField(myChannelNumber, 4, val, myWriteAPIKey);
   delay(3000); // ThingSpeak will only accept updates every 15 seconds.  
} 
