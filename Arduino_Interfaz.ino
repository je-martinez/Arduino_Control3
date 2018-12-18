#include <RFID.h>

char val; 
int ledPin = 38; 
int ledPin2 = 39; 
int ledPin3 = 40; 
int panico = 0;
char OPC = '1';

#define SDA_DIO 9
#define RESET_DIO 8 

RFID RC522(SDA_DIO, RESET_DIO);

char C[4];

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  Serial.begin(9600); 
}

void loop() {
  
 switch(OPC)
 {
   case '1':
   if (Serial.available()) 
   { 
     val = Serial.read();
   }

   if(panico == 1)
   {
    Panico();
   }

              switch(val)
              {
               case 'A':
               if(panico != 1)
                digitalWrite(ledPin, HIGH); 
               break;
               
               case 'B':
               if(panico != 1)
                digitalWrite(ledPin, LOW); 
               break;
          
               case 'C':
               if(panico != 1)
                digitalWrite(ledPin2, HIGH); 
               break;
               
               case 'D':
               if(panico != 1)
                digitalWrite(ledPin2, LOW); 
               break; 
          
               case 'E':
               if(panico != 1)
                digitalWrite(ledPin3, HIGH); 
               break; 
          
               case 'F':
               if(panico != 1)
                digitalWrite(ledPin3, LOW); 
               break; 
          
               case 'G':
               panico = 1;
               break;
          
               case 'H':
               panico = 0;
               break;

               case 'I':
               OPC = '2';
               break;
              }
              delay(1000);
               break;

     case '2':
     if (Serial.available()) 
     { 
       val = Serial.read();
     }

     switch(val)
     {
       case 'A':
       digitalWrite(ledPin, HIGH); 
       if (RC522.isCard())
       {
          RC522.readCardSerial();
          for(int i=0;i<4;i++)
          {
            C[i] = RC522.serNum[i];
          }
       }
       delay(500); 
       break;

       case 'J':
       OPC = '1';
       break;
       
     }
     break;
   }
   Serial.println(OPC);
   delay(500);
}


void Panico()
{
  if(panico == 1)
  {
    digitalWrite(ledPin, HIGH);
    delay(30);
    digitalWrite(ledPin, LOW);
    delay(30);
    digitalWrite(ledPin2, HIGH);
    delay(30);
    digitalWrite(ledPin2, LOW);
    delay(30);
    digitalWrite(ledPin3, HIGH);
    delay(30);
    digitalWrite(ledPin3, LOW);

    digitalWrite(ledPin3, HIGH);
    delay(30);
    digitalWrite(ledPin3, LOW);
    delay(30);
    digitalWrite(ledPin2, HIGH);
    delay(30);
    digitalWrite(ledPin2, LOW);
    delay(30);
    digitalWrite(ledPin, HIGH);
    delay(30);
    digitalWrite(ledPin, LOW);

    digitalWrite(ledPin2, HIGH);
    delay(30);
    digitalWrite(ledPin2, LOW);
    delay(30);
    digitalWrite(ledPin3, HIGH);
    delay(30);
    digitalWrite(ledPin3, LOW);
    delay(30);
    digitalWrite(ledPin, HIGH);
    delay(30);
    digitalWrite(ledPin, LOW);
  }
}
