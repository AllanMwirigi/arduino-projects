#include <IRremote.h>

#define ON 1
#define OFF 0

int voltage[12];
unsigned int i = 0;

IRrecv irrecv(12);
decode_results results;
unsigned long key_value = 0;

int bulbPin = 8;
int bulbState = OFF;

//--------------------setup

void setup(){
  Serial.begin(9600);
  irrecv.enableIRIn();
  irrecv.blink13(true);
  pinMode(bulbPin, OUTPUT);
}

//--------------------loop

void loop(){ 
  TranslateIR();
}

//--------------------functions


void ToggleBulb() {
  if(bulbState == OFF) {
    digitalWrite(bulbPin, HIGH);
    bulbState = ON;
    Serial.println("ON");
  }
  else {
    digitalWrite(bulbPin, LOW);
    bulbState = OFF;
    Serial.println("OFF");
  }
	
}
//-----TranslateIR-----
void TranslateIR() {
  if (irrecv.decode(&results)){
 
        if (results.value == 0XFFFFFFFF)
          results.value = key_value;

        switch(results.value){
          case 0xFD00FF://power
          ToggleBulb();
          break; 
        }
        key_value = results.value;
        irrecv.resume(); 
  }
}