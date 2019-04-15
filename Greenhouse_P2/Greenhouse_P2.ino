#include <SoftwareSerial.h>

SoftwareSerial ESP1( 3, 2 );

int sensor_pin = A0;
const int ldrPin = A1;
int output_value ;

void setup()
{
  Serial.begin(9600);                                 
  ESP1.begin(9600);
  pinMode(ldrPin, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
  int ldrStatus = analogRead(ldrPin);
  output_value= analogRead(sensor_pin);
  output_value = map(output_value,550,0,0,100);
  ESP1.print("Moisture : ");
  ESP1.print(output_value);
  ESP1.println("%");
  Serial.print("Moisture : ");
  Serial.print(output_value);
  Serial.println("%");
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


