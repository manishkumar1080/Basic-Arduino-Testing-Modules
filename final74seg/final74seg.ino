int a1 = 4;
int a2 = 5;
int a3 = 6;
int a4 = 7;
void setup()
{
pinMode(4,OUTPUT);
pinMode(5,OUTPUT);
pinMode(6,OUTPUT);
pinMode(7,OUTPUT);
}
void loop()
{
disp1(16);
}
void disp1(int num)
{
if(num == 16)
{
digitalWrite(a1, LOW);
digitalWrite(a2, LOW);
digitalWrite(a3, LOW);
digitalWrite(a4, HIGH);
}
}
