#include <TimerOne.h>
#include <math.h>

const int analogInPin4 = A4;
const int analogInPin5 = A5;
const int stat=0;
const int dp=1;

float sensorValue = 0,sensorValue1 = 0;        // value read from the pot
float outputValue = 0,finalValue=0,sum=0,finalValue1=0,finalValue2=0,finalValue3=0,midValue=0,mid2Value=0,var=0,var1=0,var2=0;        // value output to the PWM (analog out)
int i;
int inputs[16] = {2,3,4,5,6,7,8,9,10,11,12,13,A0,A1,A2,A3}; // A,B,C,D inputs
byte BCD[16][4] ={{0,0,0,0},
{1,0,0,0},
{0,1,0,0},
{1,1,0,0},
{0,0,1,0},
{1,0,1,0},
{0,1,1,0},
{1,1,1,0},
{0,0,0,1},
{1,0,0,1},
{0,1,0,1},
{1,1,0,1},
{0,0,1,1},
{1,0,1,1},
{0,1,1,1},
{1,1,1,1}}; //BCD code
int number = 0;

////////////////////////BASIC INITIALISATION//////////////////////
void setup() {
pinMode(stat,INPUT);
pinMode(dp,OUTPUT);
Timer1.initialize(1000000);
Timer1.attachInterrupt(time_control); 
for(int a = 0; a < 16; a++){
pinMode(inputs[a], OUTPUT);} //set outputs
}

/////////////////////////////////////INTERRUPT ONE SECOND//////////////////////////
void time_control(void)
{
if(digitalRead(stat)==LOW)
{
  Seven_segment(var);
  digitalWrite(dp,LOW);
}
else
{
  var2=var2/10;
  Seven_segment(var2);
  digitalWrite(dp,HIGH);
}

}

//////////////////////////////MAIN LOOP////////////////////////////
void loop() {

noInterrupts();
  interrupts();
  

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


//////////////////////DISPLAY ON SEVEN SEGMENT///////////////////////
void Seven_segment(int number)
{
  int a[4],temp,i;
  for(i=0;i<4;i++)
  {
    a[i]=number%10;
    number=number/10;
  }
 for(int c = 0; c < 4; c++)
{
digitalWrite(sensorValue, BCD[a[3]][c]);
}

 for(int c = 4; c < 8; c++)
{
digitalWrite(sensorValue, BCD[a[2]][c-4]);
}

 for(int c = 8; c < 12; c++)
{
digitalWrite(sensorValue1, BCD[a[1]][c-8]);
}

 for(int c = 12; c < 16; c++)
{
digitalWrite(sensorValue1, BCD[a[0]][c-12]);
}
}

