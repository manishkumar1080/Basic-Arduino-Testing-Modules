/*STEPPER.cpp - Simple example in creating your own Arduino Library
 
*/
 
#include <Arduino.h>
#include "STEPPER.h"


STEPPER::STEPPER(int I1, int I2,int I3, int I4){
 pinMode(I1,OUTPUT);
 pinMode(I2,OUTPUT);
 pinMode(I3,OUTPUT);
 pinMode(I4,OUTPUT);
 INPUT1=I1;INPUT2=I2;INPUT3=I3;INPUT4=I4; 
 STEP=false;
 
}
 
void STEPPER::configureStep(boolean Step){
STEP=Step;
}
 
void STEPPER::motorInput(boolean IN1,boolean IN2,boolean IN3,boolean IN4)
{
    digitalWrite(INPUT1, IN1);
    digitalWrite(INPUT2, IN2);
    digitalWrite(INPUT3, IN3);
    digitalWrite(INPUT4, IN4); 
}






void STEPPER::stopStepper()
{
motorInput(0,0,0,0); 
}



void STEPPER::turnStepper(boolean Direction,int RPM,int Angle)
{
  int i=0;
  if(!STEP)
  {
   if(Direction){
    for(i=0;i<map(Angle,0,360,0,512);i++)
   {
    motorInput(1,1,0,0);
    delayMicroseconds(RPM);
    motorInput(0,1,1,0);
    delayMicroseconds(RPM);
    motorInput(0,0,1,1);
    delayMicroseconds(RPM);
    motorInput(1,0,0,1);
    delayMicroseconds(RPM);
   }
   }
    if(!Direction){
    for(i=0;i<map(Angle,0,360,0,512);i++)   
    {
    motorInput(1,0,0,1);
    delayMicroseconds(RPM);
    motorInput(0,0,1,1);
    delayMicroseconds(RPM);
    motorInput(0,1,1,0);
    delayMicroseconds(RPM);
    motorInput(1,1,0,0);
    delayMicroseconds(RPM);
    }    
    }
  }
  if(STEP)
  {RPM=RPM/2;
   if(Direction){
    for(i=0;i<map(Angle,0,360,0,512);i++)
   {
    motorInput(1,0,0,0);
    delayMicroseconds(RPM);
    motorInput(1,1,0,0);
    delayMicroseconds(RPM);
    motorInput(0,1,0,0);
    delayMicroseconds(RPM);
    motorInput(0,1,1,0);
    delayMicroseconds(RPM);
    motorInput(0,0,1,0);
    delayMicroseconds(RPM);
    motorInput(0,0,1,1);
    delayMicroseconds(RPM);
    motorInput(0,0,0,1);
    delayMicroseconds(RPM);
    motorInput(1,0,0,1);
    delayMicroseconds(RPM);
   }
   }
    if(!Direction){
    for(i=0;i<map(Angle,0,360,0,512);i++)   
    {
    motorInput(1,0,0,1);
    delayMicroseconds(RPM);
    motorInput(0,0,0,1);
    delayMicroseconds(RPM);
    motorInput(0,0,1,1);
    delayMicroseconds(RPM);
    motorInput(0,0,1,0);
    delayMicroseconds(RPM);
    motorInput(0,1,1,0);
    delayMicroseconds(RPM);
    motorInput(0,1,0,0);
    delayMicroseconds(RPM);
    motorInput(1,1,0,0);
    delayMicroseconds(RPM);
    motorInput(1,0,0,0);
    delayMicroseconds(RPM);

    }    
    }
  }  
    delay(10);
}



void STEPPER::runStepper(boolean Direction,int RPM,int Rotation)
{
    int i=0,j=0;
    if(!STEP)
    {
    if(Direction){
    for(j=0;j<Rotation;j++){
    for(i=0;i<512;i++)
    {
    motorInput(1,1,0,0);
    delayMicroseconds(RPM);
    motorInput(0,1,1,0);
    delayMicroseconds(RPM);
    motorInput(0,0,1,1);
    delayMicroseconds(RPM);
    motorInput(1,0,0,1);
    delayMicroseconds(RPM);
    }
    }}
    if(!Direction){
    for(j=0;j<Rotation;j++){
    for(i=0;i<512;i++)   
    {
    motorInput(1,0,0,1);
    delayMicroseconds(RPM);
    motorInput(0,0,1,1);
    delayMicroseconds(RPM);
    motorInput(0,1,1,0);
    delayMicroseconds(RPM);
    motorInput(1,1,0,0);
    delayMicroseconds(RPM);
    }    
    }}}
    if(STEP)
    {RPM=RPM/2;
    if(Direction){
    for(j=0;j<Rotation;j++){
    for(i=0;i<512;i++)
    {
    motorInput(1,0,0,0);
    delayMicroseconds(RPM);
    motorInput(1,1,0,0);
    delayMicroseconds(RPM);
    motorInput(0,1,0,0);
    delayMicroseconds(RPM);
    motorInput(0,1,1,0);
    delayMicroseconds(RPM);
    motorInput(0,0,1,0);
    delayMicroseconds(RPM);
    motorInput(0,0,1,1);
    delayMicroseconds(RPM);
    motorInput(0,0,0,1);
    delayMicroseconds(RPM);
    motorInput(1,0,0,1);
    delayMicroseconds(RPM);
    }
    }}
    if(!Direction){
    for(j=0;j<Rotation;j++){
    for(i=0;i<512;i++)   
    {
    motorInput(1,0,0,1);
    delayMicroseconds(RPM);
    motorInput(0,0,0,1);
    delayMicroseconds(RPM);
    motorInput(0,0,1,1);
    delayMicroseconds(RPM);
    motorInput(0,0,1,0);
    delayMicroseconds(RPM);
    motorInput(0,1,1,0);
    delayMicroseconds(RPM);
    motorInput(0,1,0,0);
    delayMicroseconds(RPM);
    motorInput(1,1,0,0);
    delayMicroseconds(RPM);
    motorInput(1,0,0,0);
    delayMicroseconds(RPM);
    }    
    }}}    
    delay(10);
}