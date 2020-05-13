#include <EEPROM.h>
#include "Arduino.h"

void setup() {
  // put your setup code here, to run once:

Serial.begin(9600);
Serial.println("Initializing Clean Up");
for (int i = 0; i <=50 ; i ++)
{
  EEPROM.write(i,0);
  Serial.println(EEPROM.read(i));
  delay(200);
}
Serial.println("Clean up done");
}

void loop() {
  // put your main code here, to run repeatedly:

}
