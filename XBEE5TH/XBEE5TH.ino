#include <SoftwareSerial.h>

SoftwareSerial XBee(2, 3); // RX, TX
int Xbee_loop_count; 

void setup()
{
    Serial.begin(9600);
    XBee.begin(9600);

    Serial.println( "Arduino started sending bytes via XBee" );

}

void loop() {
  
    Xbee_loop_count++;
    if (Serial.available()>=21)
    {
      for(int i=0; i<24; i++){
        Serial.print(Serial.read(),HEX);
        Serial.print(","); 
      }
      Serial.println();
    }
    add_cksum(Serial.read(), sizeof(Serial.read()));
}

#define DEBUG false 

void add_cksum(byte p[], int pktsize)
{
  int cksum = 0;  // start with a zero checksum
  for (byte i = 3; i < pktsize-1; i++) {  // skip the Start and len, start with byte 4.
    // (remembering that C arrays start at 0, not 1.)
    cksum += p[i];    // Add in this byte.
  }  // next byte
  cksum &= 0xFF;        // low order 8 bits
  cksum = 0xFF - cksum; // subtract from 0xFF
  p[pktsize-1] = cksum;
  if (DEBUG) {
    Serial.print("add_cksum got ");
    Serial.println(cksum, HEX);
  }
}
