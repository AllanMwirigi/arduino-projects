#include <english.h>
#include <TTS.h>

#include "TTS.h"

TTS tts(3);
int TTSPin = 13;

void setup(void) {
  Serial.begin(9600);
  pinMode(TTSPin, OUTPUT);
}

char line[80];
int pos = 0;

void loop(void) {
  if (Serial.available() > 0) {
//    Serial.println("available");
    char c = (char)Serial.read();
    Serial.print(c);
    if (c == '\n') {
      Serial.println("here 1");
      digitalWrite(TTSPin, HIGH);
      line[pos++] = 0;
      if (line[0] == '+') {
        Serial.println("here 2");
        int p = atoi(line+1);
        tts.setPitch(p);
      } else {
        Serial.println("here 3");
        Serial.println(line);
        tts.sayText(line);
      }
      pos = 0;
      digitalWrite(TTSPin, LOW);
    } else
      line[pos++] = c;
  }
}
