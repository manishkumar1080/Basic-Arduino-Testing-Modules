// Stepper Motor Library ( Based on unipolar stepper motor 28BYJ-48 )
// This program is a demo of how to turn or rotate stepper motor using this library.
// You can also see how to configure the motor in half step or full step mode.
// web: http://www.circuitstoday.com/

// It is assumed that the Motor module is connected to
// the following pins

//      Input1  - Pin 8
//      Input2  - Pin 9
//      Input3  - Pin 10
//      Input4  - Pin 11

  #include <STEPPER.h>
  
  
  STEPPER motor(8,9,10,11); // Select the Arduino pins which is connected to the motor module
  
  
  void setup() 
  {
   motor.configureStep(Full); // Select the working mode of the motor. You can configure it in half step mode by simply replacing the keyword "Full" with "Half" 
  }
  
  
  void loop() 
  {
    
    motor.runStepper(Clockwise,High,1); //Parameter1 = Direction / Parameter2 = Speed / Parameter3 = No. of revolutions
    delay(2000);
    
    motor.turnStepper(CounterClockwise,Medium,180); //Parameter1 = Direction / Parameter2 = Speed / Parameter3 = Angle of rotation(0-360)
    delay(2000);
    
    motor.turnStepper(Clockwise,Low,145); //Parameter1 = Direction / Parameter2 = Speed / Parameter3 = Angle of rotation(0-360)
    delay(2000);
    
    motor.runStepper(CounterClockwise,High,2); //Parameter1 = Direction / Parameter2 = Speed /  Parameter3 = No. of revolutions
    delay(2000);
    motor.stopStepper();
    
  }
