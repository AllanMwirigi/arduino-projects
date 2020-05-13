
int PIR = 5; // output of pir sensor
int led = 4; // led pin
int buzzer = 2;// buzzer pin

#include <dht.h>
dht DHT;
#define DHT11_PIN 7

void setup() {
  // put your setup code here, to run once:
  pinMode(PIR, INPUT);// setting pir output as arduino input
    // pinMode(led, OUTPUT);//setting led as output
    pinMode(buzzer, OUTPUT);//setting buzzer as output
    Serial.begin(9600);//serial communication between arduino and pc
}

void loop() {
  // put your main code here, to run repeatedly:
  int chk = DHT.read11(DHT11_PIN);
  Serial.print("Temperature=");
  Serial.print(DHT.temperature);
  Serial.print(",Humidity=");
  Serial.print(DHT.humidity);

  if(digitalRead(PIR) == HIGH) {
    digitalWrite(led, HIGH); // setting led to high
    digitalWrite(buzzer, HIGH); // setting buzzer to high
    Serial.println(",Motion=1");
    }
    else {
    digitalWrite(led, LOW); // setting led to low
    digitalWrite(buzzer, LOW); // setting buzzer to low
    Serial.println(",Motion=0");
    }
    delay(2500);
}

void motionDetection(){
  if(digitalRead(PIR) == HIGH) // reading the data from the pir sensor
    {
    digitalWrite(led, HIGH); // setting led to high
    digitalWrite(buzzer, HIGH); // setting buzzer to high
    Serial.println("motion detected");
    
    }
    else {
    digitalWrite(led, LOW); // setting led to low
    digitalWrite(buzzer, LOW); // setting buzzer to low
//    Serial.println("scanning");
    }
//    delay(1000);
}

