#include<SPI.h>
volatile boolean Check;
volatile uint16_t Master_Data;

void setup()
{
  Serial.begin(9600);
  pinMode(MISO,OUTPUT);                   
  pinMode(10,INPUT);
  digitalWrite(10,LOW);
  SPCR |= _BV(SPE);                       
  Check = false;
  SPI.attachInterrupt();
  Serial.print("$$$$$$$$$$ Temperature Monitoring Screen $$$$$$$$$$");
  delay(2000);               
}

ISR(SPI_STC_vect)                        
{
    Master_Data = SPDR;            
    Check = true;
}

void loop()
{
  if(Check)                           
  {   
      if(Master_Data != 0)
      {
      	Check = false;    
      	Serial.print("Current Temperature : ");
      	Serial.println(Master_Data);
      	delay(150);
      }
  }
}
