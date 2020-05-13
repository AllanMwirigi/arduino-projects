/* @file HelloKeypad.pde
|| @version 1.0
|| @author Alexander Brevig
|| @contact alexanderbrevig@gmail.com
||
|| @description
|| | Demonstrates the simplest use of the matrix Keypad library.
|| #
*/
#include <Keypad.h>

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
//byte rowPins[ROWS] = {5, 4, 3, 2}; //connect to the row pinouts of the keypad
//byte colPins[COLS] = {9, 8, 7, 6}; //connect to the column pinouts of the keypad

byte rowPins[ROWS] = {22, 24, 26, 28}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {30, 32, 34, 36};

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

int a = 2;  //For displaying segment "a"
int b = 3;  //For displaying segment "b"
int c = 4;  //For displaying segment "c"
int d = 5;  //For displaying segment "d"
int e = 6;  //For displaying segment "e"
int f = 8;  //For displaying segment "f"
int g = 9;  //For displaying segment "g"

int rgb_red = 42, rgb_green = 44, rgb_blue = 46, counter = 0;
String pswd = "3498", entStr = "";

void setup(){
  Serial.begin(9600);
  pinMode(a, OUTPUT);  //A
  pinMode(b, OUTPUT);  //B
  pinMode(c, OUTPUT);  //C
  pinMode(d, OUTPUT);  //D
  pinMode(e, OUTPUT);  //E
  pinMode(f, OUTPUT);  //F
  pinMode(g, OUTPUT);  //G
  pinMode(rgb_red, OUTPUT);pinMode(rgb_green, OUTPUT);pinMode(rgb_blue, OUTPUT);
}
  
void loop(){
  char key = keypad.getKey();
  selectDigit(key);
  if(counter == 4){
    Serial.println(entStr);
    if(pswd.equals(entStr)){
      digitalWrite(rgb_green, HIGH);
    }
    else{
      digitalWrite(rgb_red, HIGH);
    }
  }
  
}

void selectDigit(char key){
  if (key){
    Serial.println(key);
    switch(key){
      case '1':
        displayDigit(1);
        break;
      case '2':
        displayDigit(2);
        break;
      case '3':
        displayDigit(3);
        break;
      case '4':
        displayDigit(4);
        break;
      case '5':
        displayDigit(5);
        break;
      case '6':
        displayDigit(6);
        break;
      case '7':
        displayDigit(7);
        break;
      case '8':
        displayDigit(8);
        break;
      case '9':
        displayDigit(9);
        break;
      case '0':
        displayDigit(0);
        break;
      case 'A':
        displayDigit(10);
        break;
      case 'B':
        displayDigit(11);
        break;
      case 'C':
        displayDigit(12);
        break;
      case 'D':
        displayDigit(13);
        break;
      case '#':
        digitalWrite(rgb_red, LOW);
        digitalWrite(rgb_green, LOW);
        entStr = "";
        Serial.println(entStr);
        counter = 0;
    }
    
    if(counter <= 4 && key != '#'){
      entStr.concat(key);
      counter++;
    }
  }
}

void displayDigit(int digit)
{
  turnOff();
 //Conditions for displaying segment a
 if(digit!=1 && digit != 4 && digit!= 11 && digit != 13)
 digitalWrite(a,HIGH);
 
 //Conditions for displaying segment b
 if(digit != 5 && digit != 6 && digit!=11 && digit!=12)
 digitalWrite(b,HIGH);
 
 //Conditions for displaying segment c
 if(digit !=2 && digit != 12)
 digitalWrite(c,HIGH);
 
 //Conditions for displaying segment d
 if(digit != 1 && digit !=4 && digit !=7)
 digitalWrite(d,HIGH);
 
 //Conditions for displaying segment e 
 if(digit == 2 || digit ==6 || digit == 8 || digit==0)
 digitalWrite(e,HIGH);

 if(digit==10 || digit==11 || digit==12 || digit == 13)
 digitalWrite(e, HIGH);
 
 //Conditions for displaying segment f
 if(digit != 1 && digit !=2 && digit!=3 && digit !=7 && digit != 13 && digit != 10)
 digitalWrite(f,HIGH);
 
 if (digit!=0 && digit!=1 && digit !=7 && digit!=12)
 digitalWrite(g,HIGH);
 
}
void turnOff()
{
  digitalWrite(a,LOW);
  digitalWrite(b,LOW);
  digitalWrite(c,LOW);
  digitalWrite(d,LOW);
  digitalWrite(e,LOW);
  digitalWrite(f,LOW);
  digitalWrite(g,LOW);
}

