#include <ESP8266WiFi.h>
#include <PubSubClient.h>   // Read the rest of the article
#include <stdlib.h>
 
String ssid= "Falcon"; 
String password= "marvel10";
static String temp;
static String topi;
static String batmac;
 
const char *mqtt_server = "m11.cloudmqtt.com";
const int mqtt_port = 13676;
const char *mqtt_user = "hupemwof";
const char *mqtt_pass = "T2LL5Vu9Pqng";
const char *mqtt_client_name = "arduinoClient"; // Client connections cant have the same connection name
 
#define BUFFER_SIZE 100
 
unsigned long previousMillis = 0;
const long interval = 10000;   
char state[20];
static String st,st1;
static String top;
char msg[50];
 
WiFiClient wclient;  //Declares a WifiClient Object using ESP8266WiFi
PubSubClient client(wclient, mqtt_server,mqtt_port);  //instanciates client object
 
//Function is called when, a message is recieved in the MQTT server.
void callback(const MQTT::Publish& pub) {
  topi=pub.topic();
  if (pub.has_stream()) {
    uint8_t buf[BUFFER_SIZE];
    int read;
    while (read = pub.payload_stream()->read(buf, BUFFER_SIZE)) {
    }
    pub.payload_stream()->stop();    
  } else
    temp=pub.payload_string();
      
}
 
 
void setup()  {
  // Setup console
  Serial.begin(115200);  //set the baud rate
  if (WiFi.status() != WL_CONNECTED) {  //wifi not connected?
    WiFi.begin(ssid.c_str(), password.c_str());
    if (WiFi.waitForConnectResult() != WL_CONNECTED)
      return;
  }
}
 
void loop() {
  if (WiFi.status() == WL_CONNECTED) {
  //client object makes connection to server
    if (!client.connected()) {
    //Authenticating the client object
      if (client.connect(MQTT::Connect("mqtt_client_name").set_auth(mqtt_user, mqtt_pass))) {
    //Subscribe code
        client.subscribe("nodeone");
      } else {
      }
    }
    if (client.connected())
      client.loop();
  }
          client.set_callback(callback);
        client.subscribe("nodeone");
        client.publish("test2","hello");
  
}
