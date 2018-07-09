#include <SPI.h>
#include <SD.h>


File myfile;

void setup()
{
 
  Serial.begin(9600);
  
  Serial.print("Initializing card...");
  
   pinMode(53, OUTPUT);
   
  if (!SD.begin(4)) {
    Serial.println("initialization of the SD card failed!");
    return;
  }
  Serial.println("initialization of the SDcard is done.");
  
 
  myfile = SD.open("textFile.txt", FILE_WRITE);
  
  
  if (myfile)
  {
    Serial.print("Writing to the text file...");
    myfile.println("Congratulations! You have successfully wrote on the text file.");
  
    myfile.close(); // close the file:
    Serial.println("done closing.");
  } else
  {
    Serial.println("error opening the text file!");
  }
  
  myfile = SD.open("textFile.txt");
  if (myfile)
  {
    Serial.println("textFile.txt:");
    
    while (myfile.available()) 
    {
      Serial.write(myfile.read());
    }
    myfile.close();
  } else 
  {
    Serial.println("error opening the text file!");
  }
}

void loop()
{
}

