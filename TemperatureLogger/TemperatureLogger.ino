//TemperatureLogger
//Log temperature data from an LM35 to a memory card
//dspinoz@spinoz.com.au

//PINS for LM35
#define pLM35 A0

void setup() 
{  
  Serial.begin(9600);
}

void loop() 
{
    int val = analogRead(pLM35);
    float voltage = float(val * (5.0 / 1024.0) * 1000);
    float celsius = voltage / 10.0;
    
    Serial.println(celsius);
    
    delay(500);
}
