
#include <Keypad.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(13, 12, 11, 10, 9, 8);
 
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'7','8','9','/'},
  {'4','5','6','*'},
  {'1','2','3','-'},
  {'C','0','=','+'}
};
byte rowPins[ROWS] = {4,5,6,7}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {0,1,2,3}; //connect to the column pinouts of the keypad
 
//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 
 
int relay1 = A0; 
int relay2 = A1; 
int relay3 = A2;
int relay4 = A3;
 
char keycount=0;
char code[4]; //Hold pressed keys

void setup(){
  pinMode(relay1,OUTPUT);
  pinMode(relay2,OUTPUT);
  pinMode(relay3,OUTPUT);
  pinMode(relay4,OUTPUT);
  
  lcd.begin(16, 2);
  lcd.print("Enter Password:");
  lcd.setCursor(0,1);
  lcd.cursor();    
  digitalWrite(relay1,LOW);
  digitalWrite(relay2,LOW);
  digitalWrite(relay3,LOW); 
  digitalWrite(relay4,LOW);
   //Turn off Relay (Locked)
}
   // set up the LCD's number of columns and rows: 

 
void loop(){
  char customKey = customKeypad.getKey();
 
  if (customKey)
  {      
      //lcd.print(customKey); //To display entered keys
      lcd.print(customKey);    //Do not display entered keys
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
            //Turn on Relay (Unlocked)    
     lcd.setCursor(0,1);
     lcd.print("Access Granted");
     delay(2000);      //Keep Door open for 4 Seconds
     digitalWrite(relay1,HIGH);
     delay(2000);
     digitalWrite(relay2,HIGH);
     delay(2000);
     digitalWrite(relay3,HIGH);
     delay(2000);
     digitalWrite(relay4,HIGH);
     delay(4000);
     Lock();
    }
    else
    {
      lcd.setCursor(0,1);
      lcd.print("Invalid Password");  //Display Error Message
      delay(4000); //Message delay
      Lock();
    }
  }
}

void Lock()
{
    lcd.setCursor(0,1);
    lcd.print("Relays Locked");
    delay(2000);
    lcd.setCursor(0,1);
    lcd.print("Cleared Everything"); //Clear Password
    lcd.setCursor(0,1);
    keycount=0;
    delay(1000);
    digitalWrite(relay1,LOW);
    delay(1000);
    digitalWrite(relay2,LOW);
    delay(1000);
    digitalWrite(relay3,LOW);
    delay(1000);
    digitalWrite(relay4,LOW); //Turn off Relay (Locked)
}
