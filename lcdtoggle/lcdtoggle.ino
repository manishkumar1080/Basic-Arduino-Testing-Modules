#include<LiquidCrystal.h>

LiquidCrystal lcd (2,3,4,5,6,7);
const int switchPin = 11;//the switch connect to pin 12
int switchState = 0; 


void setup()
{
 pinMode(switchPin, INPUT); //initialize thebuttonPin as input
 lcd.begin(16, 2);  
}

void loop()
{
   switchState = digitalRead(switchPin);
  if (switchState == HIGH ) //if it is,the state is HIGH
  {
  lcd.setCursor(0,0);           
  lcd.print("16x2 LCD MODULE");
  }
  else
  {
  lcd.setCursor(2,1);           
  lcd.print("HELLO WORLD");     
  }
}

