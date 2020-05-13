#include "Wire.h" // For I2C
#include "LCD.h" // For LCD
#include "LiquidCrystal_I2C.h" // Added library*
//Set the pins on the I2C chip used for LCD connections
//ADDR,EN,R/W,RS,D4,D5,D6,D7
LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7); // 0x27 is the default I2C bus address of the backpack-see article
void setup()
{
   // Set off LCD module
   lcd.begin (20,4); // 16 x 2 LCD module
   lcd.setBacklightPin(3,POSITIVE); // BL, BL_POL
   lcd.setBacklight(HIGH);
   lcd.print("Hello, World!");
   lcd.setCursor(0,1);
   lcd.print("Good Day");   
}
void loop()
{
}

