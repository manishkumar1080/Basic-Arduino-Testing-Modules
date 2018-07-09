char readChar;

void setup() {
  // put your setup code here, to run once:
pinMode(13,OUTPUT);
Serial.begin(9600);
delay(500);
Serial.print("K");
delay(500);
}

void loop() {
  // put your main code here, to run repeatedly:
if(Serial.available()>0){
  readChar=Serial.read();
  if(readChar=='O'){
    digitalWrite(13,HIGH);
    delay(5000);
    digitalWrite(13,LOW);
  }
}
if (Serial.available()>0){
  if(Serial.read() == 'K'){
    Serial.print('O');
  }
}
}
