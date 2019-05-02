#include <SoftwareSerial.h>

SoftwareSerial ESP1( 3, 2 );

const int relay1 = 4; 
const int relay3 = 5; 
int sensor_pin = A1;
const int ldrPin = A0;
int output_value ;

void setup()
{
  Serial.begin(9600);                                 
  ESP1.begin(9600);
  pinMode(ldrPin, INPUT);
  pinMode(relay1,OUTPUT);
  pinMode(relay3,OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(relay1,HIGH);
  digitalWrite(relay3,HIGH);
  delay(1000);
}

void loop()
{
  float moisture_percentage;
  int sensor_analog;
  int ldrStatus = analogRead(ldrPin);
  sensor_analog = analogRead(sensor_pin);
  moisture_percentage = ( 100 - ( (sensor_analog/1023.00) * 100 ) );
  ESP1.print("Moisture Percentage = ");
  ESP1.print(moisture_percentage);
  ESP1.println("%\n\n");
  Serial.print("Moisture Percentage = ");
  Serial.print(moisture_percentage);
  Serial.print("%\n\n");
  delay(1000);
  if (ldrStatus <= 200) 
  {
    Serial.print("Its DARK, Turn on the LED : ");
    Serial.println(ldrStatus);
    digitalWrite(LED_BUILTIN, HIGH);
    digitalWrite(relay1,HIGH);
    delay(5000);
} 
else {
  
  Serial.print("Its BRIGHT, Turn off the LED : ");
  Serial.println(ldrStatus);
  digitalWrite(LED_BUILTIN, LOW);
  digitalWrite(relay1,LOW);
  delay(5000);
}
if (moisture_percentage >= 50.0)
  {
    Serial.println("Moisture Alert!!!");
    digitalWrite(relay3, LOW);
    delay(5000);
  }
  else
  {
    Serial.println("Its just fine");
    digitalWrite(relay3, HIGH);
    delay(5000);
  }
}


