#include <RFID.h>

char val; 
int ledPin = 38; 
int ledPin2 = 39; 
int ledPin3 = 40; 
int speaker = 41; 
int panico = 0;
char OPC = '1';
int s[4];

#define SDA_DIO 9
#define RESET_DIO 8
#define BTN_1 16724175
#define BTN_2 16718055
#define BTN_3 16743045 

RFID RC522(SDA_DIO, RESET_DIO);

#include <IRremote.h>
int RECV_PIN = 13;
int led = 39;
IRrecv irrecv(RECV_PIN);
decode_results results;

char C[4];


void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(speaker, OUTPUT);
  Serial.begin(9600); 
  irrecv.enableIRIn();
}

void loop() {
  
 switch(OPC)
 {
   case '1':
   if (Serial.available()) 
   { 
     val = Serial.read();
   }

    Control_Remoto();
   
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
            s[i] = RC522.serNum[i];
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
   //Serial.println(s);
   delay(500);
}


void Panico()
{
  if(panico == 1)
  {
    digitalWrite(ledPin, HIGH);
    digitalWrite(speaker, HIGH);
    delay(30);
    digitalWrite(speaker, LOW);
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
    digitalWrite(speaker, LOW);
  }else
    {
      digitalWrite(speaker, LOW);
    }
}

void Control_Remoto(){
if (irrecv.decode(&results))
    {
     switch(results.value)
     {
       case BTN_1:
       if(digitalRead(ledPin) == HIGH)
       {
        val = 'B';
       }
       else{
        val = 'A';
        }
       break;

       case BTN_2:
       if(digitalRead(ledPin2) == HIGH)
       {
        val = 'D';
       }
       else{
        val = 'C';
        }
       break;

       case BTN_3:
       if(digitalRead(ledPin3) == HIGH)
       {
        val = 'F';
       }
       else{
        val = 'E';
        }
       break;
     }
     Serial.println(val);
     irrecv.resume(); // Receive the next value
    }
}
