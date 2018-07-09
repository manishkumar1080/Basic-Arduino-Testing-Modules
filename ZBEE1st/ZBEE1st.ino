
void setup()
{
    Serial.begin(9600);

    Serial.println( "Arduino started sending bytes via XBee" );

}

void loop() {
    // Send character via XBee to other XBee connected to Mac
    if (Serial.available()>=18)
    {
      for(int i=0; i<18; i++){
        Serial.print(Serial.read(),HEX);
        Serial.print(","); 
      }
      Serial.println();
      if (Serial.read() == "7E")
      {
      Serial.println(Serial.read(),HEX);
      Serial.println(","); 
      }
      
    }
    
}
