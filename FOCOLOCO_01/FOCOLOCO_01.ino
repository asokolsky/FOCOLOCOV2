// Adafruit Motor shield library
// copyright Adafruit Industries LLC, 2009
// this code is public domain, enjoy!
#include "OneButton.h" //this library allows buttons to call mutiple events: http://www.mathertel.de/Arduino/OneButtonLibrary.aspx
#include <LiquidCrystal.h>
#include <Encoder.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 10, 9, 8, 7);
Encoder myEnc(2, 3);
OneButton button(4, true); // Setup a OneButton on pin 4.
// Connect a stepper motor with 48 steps per revolution (7.5 degree)
// to motor port #2 (M3 and M4)

int encoderPin1 = 3;
int encoderPin2 = 2;
volatile int lastEncoded = 0;
int encoderValue;
long lastencoderValue = 0;
int lastMSB = 0;
int lastLSB = 0;
int lens;
int infinity =0 ;
int macro = 999;
int hardstop = 0;
int mark1;
int mark2;
int mark3;
int dist = 0;
int bat = 6;
char buffer [16];     //used with sprintinf to format text for LCD
int n;                //used with sprintinf to format text for LCD
long previoushardstop;
long oldPosition  = -999;

void setup() {
 
  Serial.println("Stepper test!");
  pinMode(encoderPin1, INPUT); 
  pinMode(encoderPin2, INPUT);
  digitalWrite(encoderPin1, HIGH); //turn pullup resistor on
  digitalWrite(encoderPin2, HIGH); //turn pullup resistor on

button.attachDoubleClick(infinityFunction); // link the recordFunction to be called on a doubleclick event.     
button.attachClick (macroFunction);    // link the reverseFunction to be called on a click (short click) event.   
  button.attachPress (resetFunction);   // link the playbackFunction to be called on a press (long click) event.
lcd.begin(16, 2); 
lcd.clear();
}

void loop() {
 
  long newPosition = myEnc.read();
  if (newPosition != oldPosition) {
    oldPosition = newPosition;
    hardstop = newPosition;
  }
  button.tick(); //this checks for a button press event


  
  
 hardstop = constrain(hardstop,infinity,macro);
 if (hardstop < previoushardstop)  {
   
previoushardstop = hardstop;
  } 

   if (hardstop > previoushardstop)  {
   
previoushardstop = hardstop;
   }
  
  lcd.setCursor(0, 0);
  lcd.print("STP MAC INF BAT");
  lcd.setCursor(0, 1);
 n=sprintf (buffer, "%03d %03d %03d %02d ",hardstop, macro, infinity, bat);
  lcd.print(buffer); ///< You will get “000 00 00 00 00″
}   
   

   void macroFunction(){
     macro = hardstop;
}
void infinityFunction(){
     infinity = hardstop;
}

   void resetFunction(){
     macro = 1000;
     infinity = 0;
}

