/*

-----------
 - Download the DMD library here: https://github.com/freetronics/DMD
 - Place the DMD library folder into the "arduino/libraries/" folder of your Arduino installation.
 - Get the TimerOne library from here: http://code.google.com/p/arduino-timerone/downloads/list
   or download the local copy from the DMD library page (which may be older but was used for this creation)
   and place the TimerOne library folder into the "arduino/libraries/" folder of your Arduino installation.
 - Restart the IDE.

*/

#include <SPI.h>        //SPI.h must be included as DMD is written by SPI (the IDE complains otherwise)
#include <DMD.h>        
#include <TimerOne.h>   
#include "SystemFont5x7.h"
#include "Arial_black_16.h"

//Fire up the DMD library as dmd
#define DISPLAYS_ACROSS 1
#define DISPLAYS_DOWN 1
DMD dmd(DISPLAYS_ACROSS, DISPLAYS_DOWN);
//number max of characters in your message
#define max_char 100
char message[max_char];    // stores you message
//char mess[max_char];
char r_char;               // reads each character
byte index = 0;            // defines the position into your array
int i;            
char greeting[] = "Initiating....... wait for a second..";
/*--------------------------------------------------------------------------------------
  Interrupt handler for Timer1 (TimerOne) driven DMD refresh scanning, this gets
  called at the period set in Timer1.initialize();
--------------------------------------------------------------------------------------*/
void ScanDMD()
{ 
  dmd.scanDisplayBySPI();
}

void setup(void)
{

   //initialize TimerOne's interrupt/CPU usage used to scan and refresh the display
   Timer1.initialize( 5000 );           //period in microseconds to call ScanDMD. Anything longer than 5000 (5s) and you can see flicker.
   Timer1.attachInterrupt( ScanDMD );   //attach the Timer1 interrupt to ScanDMD which goes to dmd.scanDisplayBySPI()
  
   //clear/init the DMD pixels held in RAM
   dmd.clearScreen( true );   //true is normal (all pixels off), false is negative (all pixels on)
   Serial.begin(9600);
strcpy(message,greeting);
}
void loop(void)
{
   //check if serial is avaible an before reading a new message delete's the old message
    
   if(Serial.available())
   {       
        for(i=0; i<99; i++){
            message[i] = '\0';
        } 
        //resests the index        
        index=0;
    }

    //while is reading the message 
    while(Serial.available() > 0){
       //the message can have up to 100 characters 
       dmd.clearScreen( true );
       if(index < (max_char-1)) 
       {         
           r_char = Serial.read();      // Reads a character
           message[index] = r_char;     // Stores the character in message array
           index++;                     // Increment position
          // message[index] = '\0';       // Delete the last position
             
       } 
   }
    
 //prepares the display to print our message
   dmd.selectFont(Arial_Black_16);
   //displays the message
   dmd.drawMarquee(message ,max_char,(32*DISPLAYS_ACROSS)-1 ,0);
   long start=millis();
   long timer=start;
   boolean ret=false;
   while(!ret)
   {
     if ((timer+30) < millis()) {
       ret=dmd.stepMarquee(-1,0);
       timer=millis();
     }
   }
}

