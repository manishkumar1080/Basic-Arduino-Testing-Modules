// Robo India Tutorial 
// Simple code upload the tempeature and humidity data using thingspeak.com
// Hardware: NodeMCU,DHT11

#include <DHT.h>  // Including library for dht
#include <WiFiClient.h> 
#include <ESP8266WiFi.h>
 
String apiKey = "GFBTMICEKVNL7SQE";     //  Enter your Write API key from ThingSpeak

const char *ssid =  "Advance Tech 2";     // replace with your wifi ssid and wpa2 key
const char *pass =  "advance@20";
const char* server = "api.thingspeak.com";

#define DHTPIN 0
#define DHTTYPE DHT22   // DHT22

DHT dht(DHTPIN, DHTTYPE);

float hum;  //Stores humidity value
float temp; //Stores temperature value

WiFiClient client;
 
void setup() 
{
       Serial.begin(115200);
       delay(10);
 
       Serial.println("Connecting to ");
       Serial.println(ssid);
 
 
       WiFi.begin(ssid, pass);
 
      while (WiFi.status() != WL_CONNECTED) 
     {
            delay(500);
            Serial.print(".");
     }
      Serial.println("");
      Serial.println("WiFi connected");
      Serial.println("DHT22 sensor testing");
      dht.begin(); 
      
 
}
 
void loop() 
{
  float converted = 0.00;
    
    //Read data and store it to variables hum and temp
    hum = dht.readHumidity();
    temp= dht.readTemperature();
     Serial.print(temp);
    //Print degree symbol
    Serial.write(176); 
    Serial.println("C");

    Serial.print("Humidity =");
    Serial.println(hum);
    if (client.connect(server,80))   //   "184.106.153.149" or api.thingspeak.com
                      {    
                             String postStr = apiKey;
                             postStr +="&field1=";
                             postStr += String(temp);
                             postStr +="&field2=";
                             postStr += String(hum);
                             postStr += "\r\n\r\n";
 
                             client.print("POST /update HTTP/1.1\n");
                             client.print("Host: api.thingspeak.com\n");
                             client.print("Connection: close\n");
                             client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
                             client.print("Content-Type: application/x-www-form-urlencoded\n");
                             client.print("Content-Length: ");
                             client.print(postStr.length());
                             client.print("\n\n");
                             client.print(postStr);
   
                        }
          client.stop();
 
          Serial.println("Waiting...");
  
  // thingspeak needs minimum 15 sec delay between updates, i've set it to 30 seconds
  delay(10000);
}
