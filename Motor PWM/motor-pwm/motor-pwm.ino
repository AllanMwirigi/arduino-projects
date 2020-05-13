
int Pwm1 = D1; //Nodemcu PWM pin 
int a0 = D0;
int a1 = D3;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
   pinMode(a0, OUTPUT);  
   pinMode(a1, OUTPUT);
   pinMode(Pwm1, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  analogWrite(Pwm1, 120);
    digitalWrite(a0, HIGH);
    digitalWrite(a1, LOW);
    
//    delay(5000);
//
//    analogWrite(Pwm1, 120);
//    delay(10000);
//    analogWrite(Pwm1, 250);
//    delay(5000);
}
