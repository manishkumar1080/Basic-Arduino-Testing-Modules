
#include <SPI.h>
#include <DMD2.h>
#include <fonts/SystemFont5x7.h>
#include <fonts/Arial14.h>
#include <fonts/Droid_Sans_24.h>
#include <fonts/Droid_Sans_16.h>
// Set Width to the number of displays wide you have
const int WIDTH = 1;
const int COUNTDOWN_FROM = 0;
int counter = COUNTDOWN_FROM;


const uint8_t *FONT = SystemFont5x7;
const uint8_t *FONT2 = SystemFont5x7;

const char *MESSAGE = "IT NEVER STOPS";

SoftDMD dmd(WIDTH,1);  // DMD controls the entire display
DMD_TextBox box(dmd, 0, 1);
DMD_TextBox box1(dmd,11,1);  // "box" provides a text box to automatically write to/scroll the display

long previousMillis = 0;        // will store last time box was updated
long interval = 1000;

unsigned long previousMillis2 = 0;
long interval2 = 1000;

void scroll();
void run_counter();
// the setup routine runs once when you press reset:
void setup() {
  Serial.begin(9600);
  dmd.setBrightness(255);
  //dmd.selectFont(FONT);
  dmd.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
    unsigned long currentMillis = millis();
 
  if(currentMillis - previousMillis > interval) {
    
    previousMillis = currentMillis;   

 
    if (counter <60)
    {
      dmd.selectFont(FONT);
      box.print(counter);
      box.println(F(""));
      counter++;
    }
    else
    {
      box1.clear();
      counter = 0;
      box.print(counter);
      // box.println(F(""));
      dmd.clearScreen();
    } 
    
  }

  if(currentMillis - previousMillis2 >= interval2)
  {
    previousMillis2 = currentMillis;  // Remember the time
     dmd.selectFont(FONT2);
     const char *next = MESSAGE;
     while(*next) {
     Serial.print(*next);
     box1.print(*next);
     delay(500);
     next++;
     }
  }
    
}

