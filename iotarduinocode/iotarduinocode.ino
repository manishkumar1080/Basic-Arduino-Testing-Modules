
#include <SoftwareSerial.h>

#include <Wire.h> // SCL-SCL(analog pin-5)
//SDA-SDA(analog pin-4)
#include <math.h>
#include "DHT.h"
#define DHTPIN 3
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321

const int BATpin= A3;
const int MQpin = A2;
const int CO2pin = A0;
const int trigUS = 3;
const int echoUS = 7;
const int PIR_Sens = 2;
const int Proxi = 4;
int i;
int pirState = LOW;
int value;
int duration;
int distance;
int val = 0;

const int relay1 = 10; 
const int relay2 = 11; 
const int relay3 = 12;
const int relay4 = 13;

byte buff[2];
int f1=0,f2=0,f3=0,f4=0,f5=0,f6=0,f7=0,f8=0;

String ssid="Falcon";
String password="marvel10";
 
SoftwareSerial mySerial(8, 9);      ////////rx,tx
DHT dht(DHTPIN, DHTTYPE);
void setup()
{
  dht.begin();
  Wire.begin();
  Serial.begin(115200);
  mySerial.begin(115200);
  pinMode(trigUS, OUTPUT);
  pinMode(echoUS, INPUT);
  pinMode(PIR_Sens, INPUT);
  pinMode(Proxi, INPUT);
  pinMode(relay1,OUTPUT);
  pinMode(relay2,OUTPUT);
  pinMode(relay3,OUTPUT);
  pinMode(relay4,OUTPUT);

  delay(500);
     mySerial.print("u");
     mySerial.print(ssid);
     mySerial.print("\n");
     delay(100);
     mySerial.print("p");
     mySerial.print(password);
     mySerial.print("\n");
     delay(200);
     digitalWrite(relay1,HIGH);
     digitalWrite(relay2,HIGH);
     digitalWrite(relay3,HIGH); 
     digitalWrite(relay4,HIGH);
}

void loop()
{
  char ch;
  if(mySerial.available()>0)
  {
    while(mySerial.read()!='k');
     mySerial.print("**");
     ch=mySerial.read();
     Serial.println(ch);
     switch(ch)
     {
      case '1':
                {
                //CO2_Sensor();
                  US_Sensor();
                //Relay_Control();
                // PIR_Sensor();
                // LUX_Sensor();
                 // DHT22_Sensor();
                 //Proximity_Sensor();
                 //MQ135_Sensor();
                break;
                }
      case '2':
                {
                battery();
                break;
                }
      }
  }
   
}


void US_Sensor()
{
  digitalWrite(trigUS, LOW);
  delayMicroseconds(2);
  digitalWrite(trigUS, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigUS, LOW);
  duration = pulseIn(echoUS, HIGH);
  distance = (duration/2) / 29.1;
  mySerial.print("US!");
  mySerial.print(distance);
  mySerial.print(" cm");
  mySerial.print("\n");
  delay(1000);
}

void PIR_Sensor()
{
  val = digitalRead(PIR_Sens);  // read input value
  if (val == HIGH)
  {
    if (pirState == LOW)
    {
      pirState = HIGH;
    }
  }
  else
  {
    if (pirState == HIGH)
    {
      pirState = LOW;
    }
  }
  mySerial.print("PIR!");
  if (pirState == HIGH)
  {
    mySerial.print("HIGH");
  }
  else
  {
    mySerial.print("LOW");
  }
  mySerial.print("\n");
  delay(1000);
  
}

//////////////////////////////LUX SENSOR///////////////
int BH1750_Read(int address)
{
  int i = 0;
  Wire.beginTransmission(address);
  Wire.requestFrom(address, 2);
  while (Wire.available())
  {
    buff[i] = Wire.read();  // receive one byte
    i++;
  }
  Wire.endTransmission();
  return i;

}

void BH1750_Init(int address)
{
  Wire.beginTransmission(address);
  Wire.write(0x10); //1lx reolution 120ms
  Wire.endTransmission();
}
void LUX_Sensor()
{
  int i;
  uint16_t val = 0;
  BH1750_Init(0x23);
  delay(200);
  mySerial.print("LU!");
  if (2 == BH1750_Read(0x23))
  {
    val = ((buff[0] << 8) | buff[1]) / 1.2;
    mySerial.print(val, DEC);
    mySerial.print("\n");
  }
  else
  {
    mySerial.print("NC");
    mySerial.print("\n");
  }
    mySerial.print("\n");
  delay(1000);
}

void DHT22_Sensor()
{
  int h = dht.readHumidity();
  int t = dht.readTemperature(); // Read temperature as Celsius (the default)

  mySerial.print("DH!");
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t))
  {
    mySerial.print("Failed");
    mySerial.print("\n");
    return;
  }
  else if (h == 0 || t == 0)
  {
    mySerial.print("NC");
     mySerial.print("\n");
    return;
  }
  
 mySerial.print("Humid.");
  mySerial.print(h);
  mySerial.print("% Temp.");
  mySerial.print(t);
  mySerial.print("C");
  mySerial.print("\n");
  delay(1000);
}

void Proximity_Sensor()
{
   
  mySerial.print("PR!");
  if (digitalRead(Proxi) == HIGH)
  {
    mySerial.print("HIGH");
  }
  else
  {
    mySerial.print("LOW");
  }
  mySerial.print("\n");

}

void MQ135_Sensor()
{
 
  mySerial.print("MQ!");
  value = analogRead(MQpin);
  mySerial.print(value);
  mySerial.print(" ppm");
  mySerial.print("\n");
  delay(1000);
  
}
void battery()
{
  mySerial.print("BAT!");
  value = analogRead(BATpin);
  if(value>875)
  {
    mySerial.print("OK");
  }
  else
  {
    mySerial.print("NOT OK");
  }
  mySerial.print("\n");
 
}

void CO2_Sensor()
{
  value = analogRead(CO2pin);
  delay(100);
  mySerial.print("CO!");
  mySerial.print(value);
  mySerial.print(" ppm");
  mySerial.print("\n");
  }

void Relay_Control()
{
  value = analogRead(relay1);
  value = analogRead(relay2);
  value = analogRead(relay3);
  value = analogRead(relay4);
  mySerial.print("Relays Started");
   if (distance <= "20")
 {
  delay(100);
  digitalWrite(relay1,LOW);
  delay(2000);
  digitalWrite(relay2,LOW);
  delay(2000);
  digitalWrite(relay3,LOW);
  delay(2000);
  digitalWrite(relay4,LOW);
  delay(4000);
 }
}

