//TemperatureLogger
//Log temperature data from an LM35 to a memory card using the SD library
//dspinoz@spinoz.com.au

#include <SD.h>

//PINS for LM35
#define pLM35 A0
//PINS for microsd 0544
#define pCS 10
//#define pDI 9
//#define pSCK 13
//#define pD0 12

File dataFile;

void setup() 
{  
  Serial.begin(9600);
  
  Serial.print("Initializing SD card...");
  // make sure that the default chip select pin is set to
  // output, even if you don't use it:
  pinMode(SS, OUTPUT);
  
  // see if the card is present and can be initialized:
  if (!SD.begin(pCS)) 
  {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    while (1) ;
  }
  Serial.println("card initialized.");
  
  // Open up the file we're going to log to!
  dataFile = SD.open("templog.txt", FILE_WRITE);
  if (! dataFile) 
  {
    Serial.println("error opening templog.txt");
    // Wait forever since we cant write data
    while (1) ;
  }
  
  
  
}

void loop() 
{
    int val = analogRead(pLM35);
    float voltage = float(val * (5.0 / 1024.0) * 1000);
    float celsius = voltage / 10.0;
    
    //log to serial
    Serial.println(celsius);
    
    //log temperature to the data file
    dataFile.println(celsius);
    
    //force a flush, otherwise its only every 512 bytes
    dataFile.flush();
    
    delay(1000);
}
