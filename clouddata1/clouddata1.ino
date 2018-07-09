/*
 * HTTP Client
 * Copyright (c) 2015, circuits4you.com
 * All rights reserved.
/* Connects to WiFi HotSpot. */

#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include "DHT.h"

#define DHTTYPE DHT22


/* Set these to your desired credentials. */
const char *ssid = "Falcon";  //ENTER YOUR WIFI SETTINGS <<<<<<<<<
const char *password = "marvel10";

// DHT Sensor
const int DHTPin = 4;
// Initialize DHT sensor.
DHT dht(DHTPin, DHTTYPE);

// Temporary variables
static char celsiusTemp[7];
static char fahrenheitTemp[7];
static char humidityTemp[7];


//Web address to read from
const char *host = "api.thingspeak.com";
String apiKey = "GFBTMICEKVNL7SQE";  //ENTER YOUR API KEY <<<<<<<<<<<
//=======================================================================
//                    Power on setup
//=======================================================================

void setup() {
  delay(1000);
  Serial.begin(115200);
  dht.begin();

  WiFi.mode(WIFI_STA);        //This line hides the viewing of ESP as wifi hotspot
  //WiFi.mode(WIFI_AP_STA);   //Both hotspot and client are enabled
  //WiFi.mode(WIFI_AP);       //Only Access point
  
  WiFi.begin(ssid, password);     //Connect to your WiFi router
  Serial.println("");

  Serial.print("Connecting");
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  //If connection successful show IP address in serial monitor
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP
}

//=======================================================================
//                    Main Program Loop
//=======================================================================
void loop() {
  WiFiClient client;          
  const int httpPort = 80; //Port 80 is commonly used for www
 //---------------------------------------------------------------------
 //Connect to host, host(web site) is define at top 
 if(!client.connect(host, httpPort)){
   Serial.println("Connection Failed");
   delay(300);
   return; //Keep retrying until we get connected
 }

 
 
//---------------------------------------------------------------------
  //Make GET request as pet HTTP GET Protocol format
  String ADCData;
  int adcvalue=analogRead(A0);  //Read Analog value of LDR
  ADCData = String(adcvalue);   //String to interger conversion
  String Link="GET https://api.thingspeak.com/update?api_key=GFBTMICEKVNL7SQE&field1=1234&field2=4569";  //Requeste webpage  
  Link = Link + ADCData;
  Link = Link + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close\r\n\r\n";                
  client.print(Link);
  delay(100);
  
//---------------------------------------------------------------------
 //Wait for server to respond with timeout of 5 Seconds
 int timeout=0;
 while((!client.available()) && (timeout < 1000))     //Wait 5 seconds for data
 {
   delay(10);  //Use this with time out
   timeout++;
 }
  if(timeout < 500)
 {
     while(client.available()){
        Serial.println(client.readString()); //Response from ThingSpeak       
     }
 }
 else
 {
     Serial.println("Request timeout..");
 }

 delay(5000);  //Read Web Page every 5 seconds
if (client) {
    Serial.println("New client");
    // bolean to locate when the http request ends
    boolean blank_line = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        
      if (c == '\n' && blank_line) {
            // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
            float h = dht.readHumidity();
            // Read temperature as Celsius (the default)
            float t = dht.readTemperature();
            // Read temperature as Fahrenheit (isFahrenheit = true)
            float f = dht.readTemperature(true);
            // Check if any reads failed and exit early (to try again).
            if (isnan(h) || isnan(t) || isnan(f)) {
              Serial.println("Failed to read from DHT sensor!");
              strcpy(celsiusTemp,"Failed");
              strcpy(fahrenheitTemp, "Failed");
              strcpy(humidityTemp, "Failed");         
            }
            else{
              // Computes temperature values in Celsius + Fahrenheit and Humidity
              float hic = dht.computeHeatIndex(t, h, false);       
              dtostrf(hic, 6, 2, celsiusTemp);             
              float hif = dht.computeHeatIndex(f, h);
              dtostrf(hif, 6, 2, fahrenheitTemp);         
              dtostrf(h, 6, 2, humidityTemp);
              // You can delete the following Serial.print's, it's just for debugging purposes
              Serial.print("Humidity: ");
              Serial.print(h);
              Serial.print(" %\t Temperature: ");
              Serial.print(t);
              Serial.print(" *C ");
              Serial.print(f);
              Serial.print(" *F\t Heat index: ");
              Serial.print(hic);
              Serial.print(" *C ");
              Serial.print(hif);
              Serial.print(" *F");
              Serial.print("Humidity: ");
              Serial.print(h);
              Serial.print(" %\t Temperature: ");
              Serial.print(t);
              Serial.print(" *C ");
              Serial.print(f);
              Serial.print(" *F\t Heat index: ");
              Serial.print(hic);
              Serial.print(" *C ");
              Serial.print(hif);
              Serial.println(" *F");
            }
      }
      }
    }
//---------------------------------------------------------------------
 //If data is available before time out read it.
}
}
