#include "ESP8266WiFi.h"

// KEY_LED functions
uint8_t key_led( uint8_t level)
{
  uint8_t state;
  digitalWrite(16, 1);
  pinMode(16, INPUT);
  state = digitalRead(16);
  pinMode(16, OUTPUT);
  digitalWrite(16, level);
  return state;
}

void setup() 
{
  Serial.begin(115200);
}

void loop() 
{
  // blink NodeMCU onboard led 
  uint8_t led = ((millis() % 1000) < 500);

  // Set the LED and read switch
  uint8_t gpio0 = key_led(led);

  Serial.print("GPIO16=");
  Serial.println(gpio0);
}
