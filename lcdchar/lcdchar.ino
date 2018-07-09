#include<LiquidCrystal.h>

LiquidCrystal lcd (13,12,11,10,9,8);

void setup()
{
 lcd.begin(16, 2);  
 lcd.clear();
}

void loop()
{
  int count=33;
  char ascii=0*00+33;
  while(count!=256)
  {
  lcd.setCursor(0,0);           
  lcd.print("DECIMAL = ");
  lcd.print(count);
  lcd.setCursor(0,1);           
  lcd.print("ASCII = ");     
  lcd.print(ascii);
  count++;
  ascii++;
  delay(100);
  lcd.clear();
}
}
