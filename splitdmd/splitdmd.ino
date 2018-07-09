
/*
Test sketch for split screen scrolling
NOTE that this sketch uses the Freetronics version of the DMD library available here:
https://github.com/freetronics/DMD/
but with the additional dmd.stepSplitMarquee() function.

I also suggest that you make sure this has been changed DMD.cpp
change the line:
  SPI.setClockDivider(SPI_CLOCK_DIV128);
to:
  SPI.setClockDivider(SPI_CLOCK_DIV2);  // system clock / 2 = 8MHz SPI CLK to shift registers
This provides a marked improvement in the DMD update time within the interrupt routine.
*/

#include "SPI.h"        
#include "DMD.h"        
#include "TimerOne.h"
#include "SystemFont5x7.h"

#define DISPLAYS_ACROSS 1
#define DISPLAYS_DOWN 1

DMD dmd( DISPLAYS_ACROSS , DISPLAYS_DOWN);

void ScanDMD()
{
  dmd.scanDisplayBySPI();
}

void setup()
{
  Timer1.initialize( 10000 );   // I find the default 5000 gives a visible flicker         
  Timer1.attachInterrupt( ScanDMD );  
  dmd.selectFont(SystemFont5x7);
  dmd.clearScreen( true );     // start with a blank screen
}

void loop()
{
  unsigned long time;
  int n;
  boolean ret = false;

  // Show some stationary text on the bottom half, and scrolling text on the top half
  // scrolls 3 times
  dmd.drawString(0,8,"Stays still",11,GRAPHICS_NORMAL); // the stationary string
  dmd.drawMarquee("Scrolling text",14,0,0); // set up the marquee
  time = millis();
  n=0;
  while(n<3) {
    while (!ret) {
      if ((time+30) < millis()) {
        ret = dmd.stepMarquee(0,7); // parameters are the top & bottom rows to be scrolled
        time = millis();
      }
    }
    ret = false;
    n++;
  }
  dmd.clearScreen( true );

  // Now some stationary text on the top half, and scrolling text on the bottom half
  // scrolls for 10 seconds
  dmd.drawString(0,0,"Stays still",11,GRAPHICS_NORMAL); // stationary text
  dmd.drawMarquee("Scrolling text",14,0,8); // set up the marquee
  time = millis();
  while ((millis() - time)<10000){ // loop for 10 seconds
    dmd.stepMarquee(8,15); // only scroll rows 8 to 15
    delay(30);
  } // a slightly different way to loop for stepping the marquee
    // note that this does not test for completion of the scroll, but continues until
    // the 10 second time has expired
  dmd.clearScreen( true );

  // Now a bit of fun
  dmd.drawString(0,-4,"vvvvvvvvvvv",11,GRAPHICS_NORMAL); // note the position is above a single DMD so
                                                         // only part of the text will be visible
  dmd.drawString(0,13,"^^^^^^^^^^^",11,GRAPHICS_NORMAL); // and this is too far down a single DMD so
                                                         // only part will be visible
  // these 2 lines above use partial characters displayed on the screen by placing the text at non-standard positions
  // to give a graphical highlight effect.
  dmd.drawMarquee("Scrolling text",14,0,5);
  time = millis();
  while ((millis() - time)<10000){ // again we will scroll for 10 seconds
    dmd.stepMarquee(5,11); 
    delay(30);
  }
  dmd.clearScreen( true );
}
