#include <DHT.h>

//Constants
#define DHTPIN 2     // what pin we're connected to
#define DHTTYPE DHT22   // DHT22

DHT dht(DHTPIN, DHTTYPE); // Initialize DHT sensor for normal 16mhz Arduino

//Variables
float hum;  //Stores humidity value
float temp; //Stores temperature value

void setup() 
{
  //Initialize serial port
  Serial.begin(9600);

  Serial.println("DHT22 sensor testing");
  
  //Initialize the DHT sensor
  dht.begin();  
}

void loop() 
{ 
    float converted = 0.00;
    
    //Read data and store it to variables hum and temp
    hum = dht.readHumidity();
    temp= dht.readTemperature();

    Serial.print("Celsius = ");
    Serial.print(temp);
    //Print degree symbol
    Serial.write(176); 
    Serial.println("C");

    //Fahrenheit
    //T(°F) = T(°C) × 9/5 + 32
    converted = ( temp * 1.8 ) + 32;
    Serial.print("Fahrenheit = ");
    Serial.print(converted);
    //Print degree symbol
    Serial.write(176); 
    Serial.println("F");

    //Kelvin
    //T(K) = T(°C) + 273.15          
    converted = temp + 273.15;
    Serial.print("Kelvin = ");
    Serial.print(converted);
    Serial.println(" K");

    //Rankine
    //T(°R) = (T(°C) + 273.15) × 9/5          
    converted = temp + 273.15;
    converted = (converted * 1.8);
    Serial.print("Rankin = ");
    Serial.print(converted);
    //Print degree symbol
    Serial.write(176);    
    Serial.println("R");

    Serial.print("Humidity =");
    Serial.println(hum);

    //2000mS delay between reads
    delay(2000);
}
