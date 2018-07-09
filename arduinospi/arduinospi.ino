#include <SoftwareSerial.h>

SoftwareSerial ESP1( 3, 2 );
 
void setup()
{
  Serial.begin(9600);                                    //Initialize the CS line to HIGH
  ESP1.begin(9600);
}
 
void loop()
{
  ESP1.print("10");
  ESP1.println("\n");
  delay(50);
}
