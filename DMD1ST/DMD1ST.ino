#include <SPI.h>
#include <DMD2.h>
#include <fonts/SystemFont5x7.h>

SoftDMD dmd(1,1);
// Number of P10 panels used X, Y
DMD_TextBox box(dmd, 10, 5, 16, 8); 
// Set Box (dmd, x, y, Height, Width) 
void setup() {
  dmd.setBrightness(50); // Set brightness 0 - 255 
  dmd.selectFont(SystemFont5x7); // Font used
  dmd.begin();     // Start DMD 
  box.print("HEY"); // Display TEXT SFE
}
void loop() {
}
