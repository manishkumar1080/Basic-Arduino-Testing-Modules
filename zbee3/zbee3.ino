
#include <SoftwareSerial.h>

SoftwareSerial XBee(2, 3); // RX, TX

// byte first[] = {0x7E, 0x00, 0x08, 0x01, 0x03, 0xFF, 0xFF, 0x00, 0x37, 0x38, 0x39, 0x55};
// byte framezero[] = {0x7E, 0x00, 0x08, 0x01, 0x02, 0xFF, 0xFF, 0x00, 0x33, 0x34, 0x35, 0x63};
byte frameZero[] = {0x7E, 0x00, 0x0D, 0x00, 0xD, 0xA2, 0x00, 0x29, 0x5C, 0x3C, 0x44, 0x79, 0x09, 0x01, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0xF3};     
// byte packet[] = {0x7E, 0x00, 0x0B, 0x01, 0x01, 0xFF, 0xFF, 0x00, 0x39, 0x39, 0x30, 0x30, 0x39, 0x39, 0xBB};

int Xbee_loop_count;
void setup()
{
  Serial.begin(9600);
  Serial.print("Helo");
  XBee.begin(9600);
}
void loop() {
  Xbee_loop_count++;

//  add_cksum(first, sizeof(first));
  add_cksum(frameZero, sizeof(frameZero));
//  add_cksum(frameOne, sizeof(frameOne));
//  add_cksum(packet, sizeof(packet));

 // XBee.write(hello, 20);
  XBee.write(frameZero, 17);
  ///XBee.write(125);
//  XBee.write(first, 12);
//  XBee.write(first, 12);

  delay(10000);
  //Serial.println(Xbee_loop_count);
  Serial.println();
}

#define DEBUG false   // change me!
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
