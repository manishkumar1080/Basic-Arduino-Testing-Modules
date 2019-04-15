#include <dht.h>

dht DHT;

#define DHT11_PIN

int sensor_pin = A0;
const int ldrPin = A5;
int smoke = A1;
int sensorThres = 500;

int output_value ;

void setup() {
  Serial.begin(9600);
  pinMode(ldrPin, INPUT);
  pinMode(smoke, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.println("Welcome to the Green House Monitoring System");
  delay(1000);
  
}

void loop() {
  
  int analogSensor = analogRead(smoke);
  int check = DHT.read11(DHT11_PIN);
  int ldrStatus = analogRead(ldrPin);
  output_value= analogRead(sensor_pin);
  output_value = map(output_value,550,0,0,100);

  Serial.print("Sensor's Value : ");
  Serial.println(analogSensor);
  Serial.print("Mositure : ");
  Serial.print(output_value);
  Serial.println("%");
  
  if (analogSensor > sensorThres)
  {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(1000); 
    
  }
  else
  {
    digitalWrite(LED_BUILTIN, LOW);
    delay(1000);
  }
 delay(100);
 
  Serial.print("Temperature = ");
  Serial.println(DHT.temperature,1);
  Serial.print("Humidity = ");
  Serial.println(DHT.humidity,1);
  delay(1000);
  if (ldrStatus <= 200) 
  {
    Serial.print("Its DARK, Turn on the LED : ");
    Serial.println(ldrStatus);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(1000);

} else {
  
  Serial.print("Its BRIGHT, Turn off the LED : ");
  Serial.println(ldrStatus);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);

}

}


