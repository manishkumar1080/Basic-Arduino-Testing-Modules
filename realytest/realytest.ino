                       
const int relay1 = 10; 
const int relay2 = 11; 
const int relay3 = 12;
const int relay4 = 13;

void setup()
{    
  Serial.begin(9600);
  pinMode(relay1,OUTPUT);
  pinMode(relay2,OUTPUT);
  pinMode(relay3,OUTPUT);
  pinMode(relay4,OUTPUT); 
  delay(1000);      
  digitalWrite(relay1,HIGH);
  digitalWrite(relay2,HIGH);
  digitalWrite(relay3,HIGH); 
  digitalWrite(relay4,HIGH);

}

void loop()
{

   digitalWrite(relay1,LOW);           // Turns ON Relays 1
   Serial.println("Light ON");
   delay(2000);                                      // Wait 2 seconds

   digitalWrite(relay2,LOW);          // Turns Relay Off
   Serial.println("Fan ON");
   delay(2000);

   
   digitalWrite(relay3,LOW);          // Turns Relay Off
   Serial.println("LED ON");
   delay(2000);
   
   digitalWrite(relay4,LOW);          // Turns Relay Off
   Serial.println("Appliance ON");
   delay(2000);
}
