#include <SoftwareSerial.h>
#include <dht.h>



SoftwareSerial ESP1( 3, 2 );

dht DHT;

int sensor_pin = A0;
const int ldrPin = A5;
int smoke = A1;
int sensorThres = 500;

int output_value ;

#define DHT11_PIN 5


void setup()
{
  Serial.begin(9600);                                    //Initialize the CS line to HIGH
  ESP1.begin(9600);
  pinMode(ldrPin, INPUT);
  pinMode(smoke, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  delay(1000);
}

void loop()
{
  int check = DHT.read11(DHT11_PIN);
  int analogSensor = analogRead(smoke);
  int ldrStatus = analogRead(ldrPin);
  output_value= analogRead(sensor_pin);
  output_value = map(output_value,550,0,0,100);
  ESP1.print("Temperature = ");
  ESP1.println(DHT.temperature,1);
  ESP1.print("Humidity = ");
  ESP1.println(DHT.humidity,1);
  delay(1000);
  ESP1.print("Moisture : ");
  ESP1.print(output_value);
  ESP1.println("%");
  delay(1000);
  ESP1.print("Sensor's Value : ");
  ESP1.println(analogSensor);
  delay(1000);
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
  if (ldrStatus <= 200) 
  {
    ESP1.print("Its DARK, Turn on the LED : ");
    ESP1.println(ldrStatus);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(1000);

} else {
  
  ESP1.print("Its BRIGHT, Turn off the LED : ");
  ESP1.println(ldrStatus);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
}
}


