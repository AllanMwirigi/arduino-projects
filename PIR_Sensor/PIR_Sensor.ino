
int PIR = 5; // output of pir sensor
int led = 4; // led pin
int buzzer = 2;// buzzer pin

void setup() {
    pinMode(PIR, INPUT);// setting pir output as arduino input
    // pinMode(led, OUTPUT);//setting led as output
    pinMode(buzzer, OUTPUT);//setting buzzer as output
    Serial.begin(9600);//serial communication between arduino and pc
}

void loop() {
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
    delay(1000);
}
