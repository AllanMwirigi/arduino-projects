#include <IRremote.h>

IRrecv irrecv(12);
decode_results results;
unsigned long key_value = 0;


void setup(){
  Serial.begin(9600);
  irrecv.enableIRIn();
  irrecv.blink13(true);
}

void loop(){ 
  TranslateIR();
}

void TranslateIR() {
  if (irrecv.decode(&results)){
 
    if (results.value == 0XFFFFFFFF)
      results.value = key_value;

    switch(results.value){
      case 0xFD00FF://power
      break;
      case 0xFD807F://vol+
      break;
      case 0xFD40BF://func/stop
      break;
      case 0xFD20DF://|<<
      break;
      case 0xFDA05F://>||
      break ;  
      case 0xFD609F://>>|
      break ;               
      case 0xFD10EF://down arrow
      break ;  
      case 0xFD906F://vol-
      break ;  
      case 0xFD50AF://up arrow
      break ;  
      case 0xFD30CF://0
      break ;  
      case 0xFDB04F://eq
      break ;
      case 0xFD708F://st/rept
      break ;
      case 0xFD08F7://1
      break ;
      case 0xFD8877://2
      break ;
      case 0xFD48B7://3
      break ;
      case 0xFD28D7://4
      break ;
      case 0xFDA857://5
      break ;
      case 0xFD6897://6
      break ;
      case 0xFD18E7://7
      break ;
      case 0xFD9867://8
      break ;
      case 0xFD58A7://9
      break ;      
    }
    key_value = results.value;
    irrecv.resume(); 
  }
}