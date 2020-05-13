#include <Wire.h>

#include <FastIO.h>
#include <I2CIO.h>
#include <LCD.h>
#include <LiquidCrystal.h>
#include <LiquidCrystal_I2C.h>
#include <LiquidCrystal_SR.h>
#include <LiquidCrystal_SR2W.h>
#include <LiquidCrystal_SR3W.h>

//#include <Key.h>
#include <Keypad.h>

#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
//const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
//LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//I2C pins declaration
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); 

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

byte rowPins[ROWS] = {3, 4, 5, 6}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {7, 8, 9, 10};

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

int rgb_red = 42, rgb_green = 44, rgb_blue = 46, counter = 0;
String pswd = "3498", entStr = "";
int buzzPin = 8;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(rgb_red, OUTPUT);pinMode(rgb_green, OUTPUT);pinMode(rgb_blue, OUTPUT);
  // set up the LCD's number of columns and rows:
  lcd.begin(20, 4);
//  // Print a message to the LCD.
//  lcd.print("Enter Password:");
//  pinMode(buzzPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  char key = keypad.getKey();
  if(key){
    Serial.println(key);
    displayChar(key);
  }
}

void displayChar(char val){
  lcd.print(val);
  delay(500);
}

void displayDigit(char key){
  if(key){
    Serial.println(key);
    lcd.setCursor(counter, 1);
    lcd.print('*');
    if(counter <= 4 && key != '#'){
        entStr.concat(key);
        counter++;
    }
    if(counter == 4 && key != '#'){
      Serial.println(entStr);
      if(pswd.equals(entStr)){
        digitalWrite(rgb_green, HIGH);        
        lcd.setCursor(0, 2);
        lcd.print("Password Accepted!");
        lcd.setCursor(0, 3);
      }
      else{
        digitalWrite(rgb_red, HIGH);
        lcd.setCursor(0, 2);
        lcd.print("Incorrect Password!");
        lcd.setCursor(0, 3);
        lcd.print("Enter # to try again");
        digitalWrite(buzzPin, HIGH);
        delay(1000);
        digitalWrite(buzzPin, LOW);
      }
    }
    if(key == '#'){
      digitalWrite(rgb_red, LOW);
      digitalWrite(rgb_green, LOW);
      entStr = "";
      Serial.println(entStr);
      counter = 0;
      lcd.clear();
      lcd.print("Enter Password:");
    }
    
  }
}


