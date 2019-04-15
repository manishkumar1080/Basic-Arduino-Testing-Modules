int sensor_pin = A1;
const int ldrPin = A0;

const int relay1 = 2; 
const int relay2 = 3; 
const int relay3 = 4;

int output_value ;

void setup() {

   Serial.begin(9600);
   Serial.println("Reading From the Sensor ...");
   pinMode(LED_BUILTIN, OUTPUT);  
   pinMode(ldrPin, INPUT);
   pinMode(relay1,OUTPUT);
   pinMode(relay2,OUTPUT);
   pinMode(relay3,OUTPUT);
   digitalWrite(relay1,HIGH);
   digitalWrite(relay2,HIGH);
   digitalWrite(relay3,HIGH); 
   delay(2000);

   }

void loop() {
  
  int ldrStatus = analogRead(ldrPin);

   output_value= analogRead(sensor_pin);

   output_value = map(output_value,550,0,0,100);

   Serial.print("Mositure : ");

   Serial.print(output_value);

   Serial.println("%");

   delay(1000);
   if (ldrStatus <= 200) 
  {
    Serial.print("Its DARK, Turn on the LED : ");
    Serial.println(ldrStatus);
    digitalWrite(LED_BUILTIN, HIGH);
    digitalWrite(relay1,LOW);
    digitalWrite(relay2,LOW);
    digitalWrite(relay3,LOW);
    delay(1000);

} else {
  
  Serial.print("Its BRIGHT, Turn off the LED : ");
  Serial.println(ldrStatus);
  digitalWrite(LED_BUILTIN, LOW);
  digitalWrite(relay1,HIGH);
  digitalWrite(relay2,HIGH);
  digitalWrite(relay3,HIGH);
  delay(1000);

}

   }
