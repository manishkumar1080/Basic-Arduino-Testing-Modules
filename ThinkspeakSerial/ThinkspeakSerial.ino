#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>

SoftwareSerial UNO (D2, D3);
 
String apiKey = "U2I48P1069UPN2OU";     //  Enter your Write API key from ThingSpeak

const char *ssid =  "Bonjour";     // replace with your wifi ssid and wpa2 key
const char *pass =  "marvel10";
const char* server = "api.thingspeak.com";



WiFiClient client;
                                    
void setup (void)
{
  Serial.begin(9600);
  UNO.begin(9600);
  pinMode(D2, INPUT);
  pinMode(D3, OUTPUT);
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

}  

void loop (void)
{
  char val = UNO.read();
   while(UNO.available())
   {
    Serial.print(val);
 }
 if (client.connect(server,80))   //   "184.106.153.149" or api.thingspeak.com
                      {  
                            
                             String postStr = apiKey;
                             postStr +="&field1=";
                             postStr += String(val);
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
                             Serial.print("Temperature: ");
                             Serial.print(val);
                             Serial.print(" degrees Celcius, Humidity: ");
                             Serial.println("%. Send to Thingspeak.");
                        }
          client.stop();
 
          Serial.println("Waiting...");
  delay(50);
} 
