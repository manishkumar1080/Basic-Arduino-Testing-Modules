#include <ESP8266WiFi.h>
#include <PubSubClient.h>   // Read the rest of the article
#include <stdlib.h>
 
String ssid; 
String password ;
static String temp;
static String topi;
static String batmac;
 
const char *mqtt_server = "m14.cloudmqtt.com";
const int mqtt_port = 13059;
const char *mqtt_user = "fkfpjzsx";
const char *mqtt_pass = "JdulLTIH_sGW";
const char *mqtt_client_name = "arduinoClient2"; // Client connections cant have the same connection name
 
#define BUFFER_SIZE 100
 
unsigned long previousMillis = 0;
const long interval = 10000;   
char state[20];
static String st,st1,st2;
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
   while(1)
  {
    if(Serial.available())
    {
      while(Serial.read()!='u');
      ssid=Serial.readStringUntil('\n');
      goto here;
    }
  } 
  here:
    while(1)
  {
    if(Serial.available())
    {
      while(Serial.read()!='p');
      password=Serial.readStringUntil('\n');
      goto there;
    }
  }
  there:
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
  if(temp=="ok1")
  {
    up:
    Serial.print("ok2");
    while(Serial.read()!='*');
    if(Serial.available())    
      {
        top=Serial.readStringUntil('!');
        st=Serial.readStringUntil('\n');
      }
      if(st!="OK" && st!="NOT OK")
      {
        goto up;
      }
      else
      {
        batmac=st+"#";
        batmac=batmac+WiFi.macAddress();
        client.publish("iot/extra/nodeone", batmac);
        temp="";
      }
    }
//   if (temp=="start")
//   {
//    Serial.print("start");
//    while(Serial.read()!='*');
//    if(Serial.available())    
//      {
//        top=Serial.readStringUntil('!');
//        st2=Serial.readStringUntil('\n');
//      }
//          if(st2=="")
//      {
//        goto here;
//      }
//      else
//      {
//        client.publish("iot/sensors/nodeone/us", st2);
//      }
//    temp="";
//    }
    
   if(temp=="ok")
    {
      here:
      Serial.print("ok1");
      while(Serial.read()!='*');
     if(Serial.available())    
      {
        top=Serial.readStringUntil('!');
        st1=Serial.readStringUntil('\n');
      }
      if(st1=="")
      {
        goto here;
      }
      else
      {
        client.publish("iot/sensors/nodeone/us", st1);
      }
    temp="";
    }
     client.set_callback(callback);
}


 
 


