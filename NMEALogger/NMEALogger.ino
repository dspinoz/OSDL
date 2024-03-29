//NMEALogger
//Log GPS' NMEA sentances to a memory card using the SD library
//dspinoz@spinoz.com.au
#include <SD.h>

//PINS for microsd 0544
#define pCS 10
//#define pDI 9
//#define pSCK 13
//#define pD0 12

//PINS for LEDs for memory card status
#define pLED_RED 4
#define pLED_GREEN 5

File dataFile;

void setup() 
{  
  Serial.begin(57600);
  
  pinMode(pLED_RED, OUTPUT);  
  pinMode(pLED_GREEN, OUTPUT); 
  
  digitalWrite(pLED_RED, HIGH);
  digitalWrite(pLED_GREEN, LOW);
  
  //Keep trying to initialise
  while(1)
  {
    Serial.print("Initializing SD card...");
    // make sure that the default chip select pin is set to
    // output, even if you don't use it:
    pinMode(SS, OUTPUT);
    
    // see if the card is present and can be initialized:
    if (!SD.begin(pCS)) 
    {
      Serial.println("Card failed, or not present");
      // don't do anything more:
      continue;
    }
    Serial.println("card initialized.");
    
    // Open up the file we're going to log to!
    dataFile = SD.open("GPSLOG.TXT", FILE_WRITE);
    if (! dataFile) 
    {
      Serial.println("error opening GPSLOG.TXT");
      // Wait forever since we cant write data
      continue;
    }
    
    //Successful file handle to memory card

    digitalWrite(pLED_RED, LOW);
    digitalWrite(pLED_GREEN, HIGH);

    break;
  }
}

int n = 0, i = 0;
void loop() 
{
  if (Serial.available())
  {
    //log GPS data to the file
    dataFile.write(Serial.read());
    
    if (n%200 == 0)
    {
      Serial.println("writing nmea...");
      
      //flush once a while... (200 bytes)
      dataFile.flush();
      
      //flash green led to indicate reading from GPS sensor
      if (i%2 == 0)
      {
        digitalWrite(pLED_GREEN, LOW);
      }
      else
      {
        digitalWrite(pLED_GREEN, HIGH);
      }
      
      i++;
      
      n=0;
    }
    
    n++;
  }
}
