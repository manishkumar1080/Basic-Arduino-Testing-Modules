void setup() {
  // initialize both serial ports:
  Serial.begin(9600);
}

void loop() {
  // read from port 1, send to port 0:

  // read from port 0, send to port 1:
  if (Serial.available()) {
    int inByte = Serial.read();
    Serial.println(inByte);
  }
}
