#include<ESP8266WiFi.h>
#include<ESP8266HTTPClient.h>
#include<ESP8266WebServer.h>
#include<SPI.h>
#include<DMD2.h>
#include<fonts/SystemFont5x7.h>
#include<fonts/Arial14.h>

/////////////////// Constants ////////////////////
const char *ssid = "Falcon"; // change according to your Network - cannot be longer than 32 characters!
const char *pass = "marvel10"; // change according to your Network

const uint8_t *FONT = Arial14;
//const uint8_t *FONT = SystemFont5x7;

const char *MESSAGE = "abcdefghijklmnopqrstuvwxyz";
//char message[5] = "abcd";

HTTPClient http;
const int WIDTH = 1;

SPIDMD dmd(WIDTH,1); // DMD controls the entire display
DMD_TextBox box(dmd); // "box" provides a text box to automatically write to/scroll the display

//int indexStop =0;

// You can change to a smaller font (two lines) by commenting this line,
// and uncommenting the line after it:

void setup() {
Serial.begin(9600);

Serial.println("Booting....");
int retries = 0;
WiFi.mode(WIFI_STA);
WiFi.begin(ssid, pass);
while ((WiFi.status() != WL_CONNECTED) && (retries < 10)) {
retries++;
delay(500);
Serial.print(".");
}

if (WiFi.status() == WL_CONNECTED) {
Serial.println("WiFi connected");
Serial.println("IP address: ");
Serial.println(WiFi.localIP());

Serial.println("Ready!");
Serial.println("======================================================");


dmd.setBrightness(255);
dmd.selectFont(FONT);
dmd.begin();

}

}

void loop() {
// put your main code here, to run repeatedly:

const char *next = MESSAGE;
while(*next) {
Serial.print(*next);
box.print(*next);
delay(200);
next++;
}
}
