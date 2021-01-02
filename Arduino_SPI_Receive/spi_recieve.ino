#include<SPI.h>
volatile boolean received;
volatile uint16_t  Slavereceived, Slavereceived2;

void setup()
{
  Serial.begin(9600);
  pinMode(MISO,OUTPUT);                   
  pinMode(10,INPUT);
  digitalWrite(10,LOW);
  SPCR |= _BV(SPE);                       
  received = false;
  SPI.attachInterrupt();
  Serial.print("SYSTEM BOOTING>...........");
  delay(2000);
  Serial.print("SYSTEM READY");                 
}


ISR (SPI_STC_vect)                        
{
    Slavereceived = SPDR;            
    received = true;
}

 

void loop()
{
  if(received)                           
  {   
      if(Slavereceived != 0)
      {
      received = false;    
      Serial.print("Temperature is  ");
      Serial.println(Slavereceived);
      delay(100);
      }
  }
}
