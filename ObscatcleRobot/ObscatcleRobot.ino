
const int trig = 8;

const int echo = 7;

int duration = 0;

int inches = 0;

// for right motor 
const int controlPin1 = 5;

const int controlPin2 = 2;

const int enablePin1 = 9;

// for left motor 
const int controlPin3 = 3;

const int controlPin4 = 4;

const int enablePin2 = 11;


void setup() {
  Serial.begin(9600);
  
  // for distance sensor
  pinMode(trig,OUTPUT);
  pinMode(echo, INPUT);
  
  // for right motor
  pinMode(controlPin1, OUTPUT);
  pinMode(controlPin2, OUTPUT);
  pinMode(enablePin1, OUTPUT); 
  
  //turn the motor off, initially
  digitalWrite(enablePin1, LOW);
  
  // for left motor
  pinMode(controlPin3, OUTPUT);
  pinMode(controlPin4, OUTPUT);
  pinMode(enablePin2, OUTPUT); 
  
  //turn the motor off, initially
  digitalWrite(enablePin2, LOW); }

void loop() {
  
  // for distance sensor
  digitalWrite(trig,LOW);
  delay(0.001);
  digitalWrite(trig,HIGH);
  delay (0.01);
  digitalWrite(trig, LOW);
  duration = pulseIn(echo,HIGH);
  inches = duration /74/2;
  Serial.print("inches: ");
  Serial.print(inches);
  Serial.print("");
  Serial.println();
  delay (5);
  
  if (inches <5){
 
    analogWrite (enablePin1, 200);
    digitalWrite (controlPin1, LOW);
    digitalWrite (controlPin2, HIGH);
    analogWrite (enablePin2, 200);
    digitalWrite (controlPin3, LOW);
    digitalWrite (controlPin4, HIGH); 
    }
    
    else if (inches >=5 and inches <9 )
    {
      digitalWrite (controlPin1, LOW);
      digitalWrite (controlPin2, LOW);
      analogWrite (enablePin1, 0);
      digitalWrite (controlPin3, LOW);
      digitalWrite (controlPin4, LOW);
      analogWrite (enablePin2, 0); 
      }
      
      else if (inches >=9)
      {
        analogWrite (enablePin1, 255);
        digitalWrite (controlPin1, HIGH);
        digitalWrite (controlPin2, LOW);
        analogWrite (enablePin2, 255);
        digitalWrite (controlPin3, HIGH);
        digitalWrite (controlPin4, LOW); 
        }

}

