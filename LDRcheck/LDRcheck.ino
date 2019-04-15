
const int ldrPin = A0;

void setup() {
  
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(ldrPin, INPUT);
}


void loop() {
  
  int ldrStatus = analogRead(ldrPin);
  if (ldrStatus <= 200) 
  {
    Serial.print("Its DARK, Turn on the LED : ");
    Serial.println(ldrStatus);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(1000);

} else {
  
  Serial.print("Its BRIGHT, Turn off the LED : ");
  Serial.println(ldrStatus);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);

}

}
