#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
 
// Replace with your network credentials
const char* ssid = "Falcon";
const char* password = "marvel10";
 
ESP8266WebServer server(80);   //instantiate server at port 80 (http port)
 
String page = "";
const int trigPin = 8;            // Making the arduino's pin 8 as the trig pin of ultrasonic sensor
const int echoPin = 9;            // Making the arduino's pin 9 as the echo pin of the ultrasonic sensor
// defining two variable for measuring the distance
long duration;
int distance;



void setup(void){
  //the HTML of the web page
  page = "<h1>Simple NodeMCU Web Server</h1><p><a href=\"LEDOn\"><button>ON</button></a>&nbsp;<a href=\"LEDOff\"><button>OFF</button></a></p>";
  //make the LED pin output and initially turned off
  pinMode(trigPin, OUTPUT);   // Setting the trigPin as Output pin
  pinMode(echoPin, INPUT); 
   
  delay(1000);
  Serial.begin(115200);
  WiFi.begin(ssid, password); //begin WiFi connection
  Serial.println("");
 
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
   Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
   
  server.on("/", [](){
    server.send(200, "text/html", page);
  });
  server.on("/LEDOn", [](){
    server.send(200, "text/html", page);
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);    
  });
  server.on("/LEDOff", [](){
    server.send(200, "text/html", page);
    digitalWrite(trigPin, HIGH); 
    delayMicroseconds(10);
  });
  server.on("/LEDOff", [](){
    server.send(200, "text/html", page);
    digitalWrite(trigPin, LOW);   
    duration = pulseIn(echoPin, HIGH);  // reading the echopin which will tell us that how much time the signal takes to come back 
    distance= duration*0.034/2;    
  });
  server.begin();
  Serial.println("Web server started!");
}
 
void loop(void){
  server.handleClient();
}
