char a[20];
void setup()
{
    Serial.begin(9600);

    Serial.println( "Arduino started sending bytes via XBee" );

}

void loop() {
    // Send character via XBee to other XBee connected to Mac
    if (Serial.available()>0)
    {
      for(int i=0;i<18;i++)
      {
        a[i]=Serial.read();
       Serial.print(a[i]);
      Serial.print(",");
      }
  Serial.println("");
    }
    }
    
