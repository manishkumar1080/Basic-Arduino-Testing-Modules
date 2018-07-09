#include <SPI.h>        
#include <DMD.h>   
#include <TimerOne.h>  
#include "SystemFont5x7.h"
#include "Arial_black_16.h"

#define DISPLAYS_ACROSS 1
#define DISPLAYS_DOWN 1
DMD dmd(DISPLAYS_ACROSS, DISPLAYS_DOWN);

#define max_char 100
char m[max_char]; 
char a[100];
int b[100];  
int i;     
int j;
int k;       
char greeting[] = "Wait";


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
            m[i] = '\0';
        }        
        k = 0;
    }

    if(Serial.available() > 0){ 
      a[i]=Serial.read();
      i++;    
       } 
       for(j=0;j<i;j++){
        b[i]=(a[i]-48);
   }
   delay(1000);
   dmd.selectFont(System5x7);
   dmd.drawMarquee(greeting ,max_char,(32*DISPLAYS_ACROSS)-1 ,1);
   delay(5000);
   long start=millis();
   long timer=start;
   boolean ret=false;
   while(!ret)
   {
     if ((timer+k) < millis()) {
       ret=dmd.stepMarquee(-1,0);
       timer=millis();
     }
   }
    }
