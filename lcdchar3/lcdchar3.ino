#include<LiquidCrystal.h>

LiquidCrystal lcd (13,12,11,10,9,8);

void setup()
{
 lcd.begin(16, 2);  
 lcd.clear();
}

void loop()
{
  int count,i;
  char ascii;
  count=i;
  i=0;
  while(i<=235)
  {
    ascii=0*00+i;
  lcd.setCursor(0,0);           
  lcd.print("DECIMAL = ");
  lcd.print(i);
  lcd.setCursor(0,1);           
  lcd.print("ASCII = ");     
  lcd.print(ascii);
  count++;
  ascii++;
  delay(2000);
  lcd.clear();
}
}
