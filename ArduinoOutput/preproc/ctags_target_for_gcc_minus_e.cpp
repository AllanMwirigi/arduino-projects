# 1 "f:\\Projects\\Arduino\\Fade_LED\\Fade_LED.ino"
# 1 "f:\\Projects\\Arduino\\Fade_LED\\Fade_LED.ino"

int LED = 11;

void setup(){
    pinMode(LED, 0x1);
}

void loop(){
    digitalWrite(LED, 0x1);
    delay(100);
    digitalWrite(LED, 0x0);
    delay(100);
}
