#include <Arduino.h>
#line 1 "f:\\Projects\\Arduino\\Fade_LED\\Fade_LED.ino"
#line 1 "f:\\Projects\\Arduino\\Fade_LED\\Fade_LED.ino"

int LED = 11;

#line 4 "f:\\Projects\\Arduino\\Fade_LED\\Fade_LED.ino"
void setup();
#line 8 "f:\\Projects\\Arduino\\Fade_LED\\Fade_LED.ino"
void loop();
#line 4 "f:\\Projects\\Arduino\\Fade_LED\\Fade_LED.ino"
void setup(){
    pinMode(LED, OUTPUT);
}

void loop(){
    digitalWrite(LED, HIGH);
    delay(100);
    digitalWrite(LED, LOW);
    delay(100);
}
