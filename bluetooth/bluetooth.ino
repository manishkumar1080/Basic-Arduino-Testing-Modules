#define relay A0
#define interval 1000

String ah;
void setup() {
  Serial.begin(9600);
}
void loop()
{
  if(Serial.available()>0)
  {
    Serial.print(Serial.readStringUntil('\n'));
    Serial.println();
    Serial.println();
   Serial.print("time");
   Serial.print("to go");Serial.println();Serial.println();
  }
}
