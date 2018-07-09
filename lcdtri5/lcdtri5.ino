#include <TimerOne.h>
#include <math.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(2,3,4,5,6,7);

const int switchPin = 11;//the switch connect to pin 12
int switchState = 0;
const int analogInPin2 = A2;
const int analogInPin3 = A3;
const int analogInPin4 = A4;
const int analogInPin5 = A5;

const int freq_count =8;
const int stat=10;

float sensorValue = 0, SensorValue = 0,sensorValue1 = 0;
float outputValue = 0,finalValue=0,sum=0,finalValue1=0,finalValue2=0,finalValue3=0,midValue=0,mid2Value=0,var=0,var1=0,var2=0; // value read from the pot
float a,y=0;
int i,cf,count;  

void setup() {
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("  ADVANCE TECH");
  delay(1000);
  Timer1.initialize(1000000);
  pinMode(switchPin, INPUT);
  Timer1.attachInterrupt(time_control);
}

void time_control(void)
{
  if(digitalRead(switchPin)==HIGH)
  {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("I1=");
  lcd.print(sensorValue);
  lcd.print("mA");
  lcd.setCursor(0, 1);
  lcd.print("V1=");
  lcd.print(sensorValue1);
  lcd.print("mV");
  }

  else
  {
  if(y!=a) 
{
  if(count==0)
  {
  lcd.clear();
  lcd.setCursor(6, 0);
  lcd.print("SINE");
  }
   else if(count==1)
  {
  lcd.clear();
  lcd.setCursor(6, 0);
  lcd.print("TRIANGLE");
  }
   else if(count==2)
  {
  lcd.clear();
  lcd.setCursor(6, 0);
  lcd.print("SQUARE");
  }
  lcd.setCursor(0, 1);
  lcd.print("freq=");
  lcd.print(cf);
  lcd.print("Hz");
  lcd.setCursor(7, 1);
  lcd.print("Ampl=");
  lcd.print(a);
  lcd.print("V");
  cf=0;
  y=a;
}
else
{
  delay(100);
}
  }
}

void loop() {
  
  noInterrupts();
  interrupts();

  switchState = digitalRead(switchPin);
  if (switchState == HIGH ) //if it is,the state is HIGH
  {
     sensorValue = analogRead(analogInPin4);
    outputValue = 0.244*sensorValue; //w.r.t 10ohm
    midValue=0.945*midValue+0.0549*outputValue;
    finalValue=0.945*finalValue+0.0549*midValue;
    var = round(finalValue);
    
    sensorValue1 = analogRead(analogInPin5);
    outputValue =sensorValue1*0.122*32.076 ; //w.r.t 10k
    mid2Value=0.945*mid2Value+0.0549*outputValue;
    finalValue2=0.945*finalValue2+0.0549*mid2Value;
    var2 = round(finalValue2);
}
  else
  {
     if(digitalRead(stat)==LOW)
{
  count++;
  if(count>=3)
  {
    count=0;
  }
}
  ///////////////////////////////sine////////////////////////////////
  if(count==0)
    {
      SensorValue=analogRead(analogInPin2);// read analog values from pin A0 across capacitor
      if(SensorValue>=0&& SensorValue<42)
        {
          a=SensorValue*0.02381;
        }
      else if(SensorValue>=42 && SensorValue<128)
        {
          a=SensorValue*0.011628 +0.511628;
        }
     else if(SensorValue>=128 && SensorValue<228)
        {
          a=SensorValue*0.01 +0.72;
        }
     else if(SensorValue>=228 && SensorValue<320)
        {
          a=SensorValue*0.01087 +0.521739;
        }
     else if(SensorValue>=320 && SensorValue<418)
        {
          a=SensorValue*0.010204 +0.734694;
        }
    else if(SensorValue>=418 && SensorValue<510)
        { 
          a=SensorValue*0.01087+0.456522;
        }
    else if(SensorValue>=510 && SensorValue<608)
        { 
          a=SensorValue*0.010204 +0.795918;
        }
    else if(SensorValue>=608 && SensorValue<708)
        {
          a=SensorValue*0.01+0.92;
        }
    else if(SensorValue>=708 && SensorValue<790)
        {
          a=SensorValue*0.012195-0.63415;
        }
    else if(SensorValue>=790 && SensorValue<880)
        {
          a=SensorValue*0.011111+0.222222;
        }
   else if(SensorValue>=880 && SensorValue<930)
        {
          a=SensorValue*0.02-7.6;
        }
   else if(SensorValue>=930 && SensorValue<1000)
        {
          a=SensorValue*0.014286-2.28571;
        }
   else if(SensorValue>=1000)
        {
           a=SensorValue*0.043478-31.4783;
        }
   else
        {
           a=SensorValue*0.01290322;
        }
  }

   ///////////////////////////////triangle////////////////////////////////
  else if(count==1)
  {
    SensorValue=analogRead(analogInPin2);  
  }
   ///////////////////////////////square////////////////////////////////
else if(count==2)
  {
    SensorValue=analogRead(analogInPin3);  
  }
  }
  if(digitalRead(freq_count)==LOW)
  {
    cf++;
  }
}

