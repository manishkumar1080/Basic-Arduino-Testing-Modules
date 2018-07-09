#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const int trigPin = D2;            // Making the arduino's pin 8 as the trig pin of ultrasonic sensor
const int echoPin = D3;            // Making the arduino's pin 9 as the echo pin of the ultrasonic sensor
// defining two variable for measuring the distance
long duration;
int distance;

char ssid[] = "Falcon"; //  Change this to your network SSID (name).
char pass[] = "marvel10";  // Change this your network password
char mqttUserName[] = "manishk07";  // Can be any name.
char mqttPass[] = " NHJAEBTQVYXB9GML";  // Change this your MQTT API Key from Account > MyProfile.
char writeAPIKey[] = "P045OP5M1LPSX2NJ";    // Change to your channel Write API Key.
long channelID = 534332;

static const char alphanum[] ="0123456789"
                              "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                              "abcdefghijklmnopqrstuvwxyz";  // For random generation of client ID.

WiFiClient client;  // Initialize the Wifi client library.
PubSubClient mqttClient(client); // Initialize the PuBSubClient library.
const char* server = "mqtt.thingspeak.com"; 

unsigned long lastConnectionTime = 0; 
const unsigned long postingInterval = 20L * 1000L; // 

void setup() {
  
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);   // Setting the trigPin as Output pin
  pinMode(echoPin, INPUT); 
  int status = WL_IDLE_STATUS;  // Set a temporary WiFi status.

  // Attempt to connect to WiFi network
  while (status != WL_CONNECTED) 
  {
    status = WiFi.begin(ssid, pass); // Connect to WPA/WPA2 Wi-Fi network.
    delay(5000);
  }

  Serial.println("Connected to wifi");
  mqttClient.setServer(server, 1883);   // Set the MQTT broker details.
}

void loop() {

 // Reconnect if MQTT client is not connected.
  if (!mqttClient.connected()) 
  {
    reconnect();
  }

  mqttClient.loop();   // Call the loop continuously to establish connection to the server.

  // If interval time has passed since the last connection, Publish data to ThingSpeak
  if (millis() - lastConnectionTime > postingInterval) 
  {
    mqttpublish();
  }
}

void reconnect() 
{
  char clientID[10];

  // Loop until we're reconnected
  while (!mqttClient.connected()) 
  {
    Serial.print("Attempting MQTT connection...");
    // Generate ClientID
    for (int i = 0; i < 8; i++) {
        clientID[i] = alphanum[random(51)];
    }
    clientID[8]='\0';

    // Connect to the MQTT broker
    if (mqttClient.connect(clientID,mqttUserName,mqttPass)) 
    {
      Serial.println("connected");
    } else 
    {
      Serial.print("failed, rc=");
      // Print to know why the connection failed.
      Serial.print(mqttClient.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void mqttpublish() {
  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);   
  duration = pulseIn(echoPin, HIGH);  // reading the echopin which will tell us that how much time the signal takes to come back 
  distance= duration*0.034/2;
  Serial.println(distance);

  String data = String(distance, DEC);
  int length = data.length();
  char msgBuffer[length];
  data.toCharArray(msgBuffer,length+1);
  Serial.println(msgBuffer);
  
  // Create a topic string and publish data to ThingSpeak channel feed. 
  String topicString ="channels/" + String( channelID ) + "/publish/"+String(writeAPIKey);
  length=topicString.length();
  char topicBuffer[length];
  topicString.toCharArray(topicBuffer,length+1);
 
  mqttClient.publish( topicBuffer, msgBuffer );

  lastConnectionTime = millis();
}
