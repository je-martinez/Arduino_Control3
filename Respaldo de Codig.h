#include <RFID.h>
#include <SPI.h>

char val;
int ledPin = 38; 
int ledPin2 = 39; 
int ledPin3 = 40; 
int speaker = 41; 
int panico = 0;
int block_panico = 0;
char OPC = '1';
int s[4];
int x[3];

#define SDA_DIO 9
#define RESET_DIO 8
#define BTN_1 16724175
#define BTN_2 16718055
#define BTN_3 16743045
#define BTN_0 16738455 

RFID RC522(SDA_DIO, RESET_DIO);

#include <IRremote.h>
int RECV_PIN = 13;
int led = 39;
IRrecv irrecv(RECV_PIN);
decode_results results;

#include <Keypad.h>
 
const byte rowsCount = 4;
const byte columsCount = 4;
 
char keys[rowsCount][columsCount] = {
   { '1','2','3', 'A' },
   { '4','5','6', 'B' },
   { '7','8','9', 'C' },
   { '*','0','#', 'D' }
};
 
const byte rowPins[rowsCount] = { 24, 26, 28, 30};
const byte columnPins[columsCount] = { 25, 27, 29, 31 };
 
Keypad keypad = Keypad(makeKeymap(keys), rowPins, columnPins, rowsCount, columsCount);

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(speaker, OUTPUT);
  Serial.begin(9600); 
  irrecv.enableIRIn();
  SPI.begin();
  RC522.init();
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
    Leer_Teclado();
   
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
               if(block_panico != 1)
               {
                 panico = 1;
               }
               break;
          
               case 'H':
               if(block_panico != 1)
               {
                 panico = 0;
               }
               break;

               case 'I':
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
        Serial.println("Entre");
          RC522.readCardSerial();
          for(int i=0;i<4;i++)
          {
            x[i] = RC522.serNum[i];
          }
          char ABC[4];
          ABC[0] = RC522.serNum[0];
          ABC[1] = '\0';
          Serial.println(ABC);
       } 
       //delay(500); 
       break;

       case 'J':
       OPC = '1';
       break;
       
     }
     break;
   }
   //Serial.println(x);
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

       case BTN_0:
       if(block_panico != 1)
       {
        panico = panico == 1 ? 0:1;
       }
       break;
     }
     Serial.println(results.value);
     irrecv.resume(); // Receive the next value
    }
}

void Leer_Teclado()
{
   char key = keypad.getKey();
   if (key) {
      Serial.println(key);
   }
}