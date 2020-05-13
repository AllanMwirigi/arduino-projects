int led=13;
int button=12;

void setup() {
  // put your setup code here, to run once:
pinMode(led, OUTPUT);
pinMode(button, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
int condition=digitalRead(button);
if(condition==HIGH){
  digitalWrite(led, HIGH);}
 else{
   digitalWrite(led, LOW);}
}

