#include <SPI.h>        
#include <DMD.h>   
#include <TimerOne.h>  
#include "SystemFont5x7.h"
#include "Arial_black_16.h"

#define DISPLAYS_ACROSS 1
#define DISPLAYS_DOWN 1
DMD dmd(DISPLAYS_ACROSS, DISPLAYS_DOWN);

#define max_char 100
char message[max_char];    
char r_char;            
byte index = 0;       
int i;
int k;            
char greeting[] = "Wait";
char p;



void ScanDMD()
{ 
  dmd.scanDisplayBySPI();
}


void setup(void)
{

   Timer1.initialize( 5000 );         
   Timer1.attachInterrupt( ScanDMD ); 
   dmd.clearScreen( true ); 
   Serial.begin(9600);
   strcpy(message,greeting);
}

void loop(void)
{
  dmd.clearScreen( true );
  dmd.selectFont(SystemFont5x7);
  dmd.drawBox(  0,  0, (32*DISPLAYS_ACROSS)-1, (16*DISPLAYS_DOWN)-1, GRAPHICS_NORMAL );
  delay(1000);
   if(Serial.available())
   {       
        for(i=0; i<99; i++){
            message[i] = '\0';
        }        
        index=0;
    }

    while(Serial.available() > 0){ 
       if(index < (max_char-1)) 
       {         
           r_char = Serial.read();
           message[index] = r_char;     
           index++;
             
       } 
   }
   delay(1000);
   dmd.selectFont(System5x7);
   dmd.drawMarquee(message ,max_char,(32*DISPLAYS_ACROSS)-1 ,1);
   dmd.drawString(  2,  7, message, 5, GRAPHICS_NORMAL );
   delay(5000);
   long start=millis();
   long timer=start;
   boolean ret=false;
   while(!ret)
   {
     if ((timer+100) < millis()) {
       ret=dmd.stepMarquee(-1,0);
       timer=millis();
     }
   }
    }
