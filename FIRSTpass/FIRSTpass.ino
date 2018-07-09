
#include <Keypad.h>
#include <LiquidCrystal.h>
 
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(9, 8, 7, 6, 5, 4);
 
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'7','8','9','/'},
  {'4','5','6','*'},
  {'1','2','3','-'},
  {'C','0','=','+'}
};
byte rowPins[ROWS] = {3, 2, 19, 18}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {17, 16, 15, 14}; //connect to the column pinouts of the keypad
 
//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 
 
const int LED_RED=10; //Red LED
const int LED_GREEN=11; //Green LED
const int RELAY=12; //Lock Relay or motor
 
char keycount=0;
char code[4]; //Hold pressed keys

void setup(){
  pinMode(LED_RED,OUTPUT);
  pinMode(LED_GREEN,OUTPUT);  
  pinMode(RELAY,OUTPUT);  
  
   // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Password Access:");
  lcd.setCursor(0,1); //Move coursor to second Line
 // Turn on the cursor
  lcd.cursor();
  digitalWrite(LED_GREEN,HIGH);  //Green LED Off
  digitalWrite(LED_RED,LOW);     //Red LED On
  digitalWrite(RELAY,LOW);       //Turn off Relay (Locked)
}
 
void loop(){
  char customKey = customKeypad.getKey();
 
  if (customKey && (keycount<4) && (customKey !='=') && (customKey !='C')){      
      //lcd.print(customKey); //To display entered keys
      lcd.print('*');    //Do not display entered keys
      code[keycount]=customKey;
      keycount++;
  }
  
  if(customKey == 'C')      //Cancel/Lock Key is pressed clear display and lock
  {
    Lock();    //Lock and clear display
  }
  
  if(customKey == '=')   //Check Password and Unlock
  {
    if((code[0]=='1') && (code[1]=='2') && (code[2]=='3') && (code[3]=='4'))  //Match the password
    {
      digitalWrite(LED_GREEN,LOW);  //Green LED Off
      digitalWrite(LED_RED,HIGH);     //Red LED On
      digitalWrite(RELAY,HIGH);       //Turn on Relay (Unlocked)    
      lcd.setCursor(0,1);
      lcd.print("Access Granted");
      delay(400);      //Keep Door open for 4 Seconds
      Lock();
    }
    else
    {
      lcd.setCursor(0,1);
      lcd.print("Invalid Password");  //Display Error Message
      delay(1500); //Message delay
      Lock();
    }
  }
}
  
void Lock()
{
    lcd.setCursor(0,1);
    lcd.print("Relays Locked");
    delay(150);
    lcd.setCursor(0,1);
    lcd.print("Cleared Everything"); //Clear Password
    lcd.setCursor(0,1);
    keycount=0;
    digitalWrite(LED_GREEN,HIGH);  //Green LED Off
    digitalWrite(LED_RED,LOW);     //Red LED On
    digitalWrite(RELAY,LOW);       //Turn off Relay (Locked)
}
