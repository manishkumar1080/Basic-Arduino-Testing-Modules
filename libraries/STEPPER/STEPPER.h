 /*STEPPER.h - Simple example in creating your own Arduino Library

*/
 
#ifndef STEPPER_h
#define STEPPER_h
 

#include "Arduino.h"
const int Low =6000;
const int Medium =3000;
const int High =2000;
const boolean CounterClockwise =false;
const boolean Clockwise =true;
const boolean Full =false;
const boolean Half =true;


 

 
class STEPPER
{
public:
  boolean STEP;
  STEPPER(int I1, int I2,int I3, int I4);
  void configureStep(boolean Step);
  void stopStepper();  
  void turnStepper(boolean Direction,int RPM,int Angle);
  void runStepper(boolean Direction,int RPM,int Rotation); 
  
private:
  int INPUT1,INPUT2,INPUT3,INPUT4;
  void motorInput(boolean IN1,boolean IN2,boolean IN3,boolean IN4);

  
};
 
#endif
