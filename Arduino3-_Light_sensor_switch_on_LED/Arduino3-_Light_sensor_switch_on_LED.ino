int led=13;
int lightsensor=A1;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  pinMode(lightsensor,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int value=analogRead(lightsensor);
  Serial.println(value);
  if(value < 650){
    digitalWrite(led, LOW);}
  else{
    digitalWrite(led, HIGH);}
    
  delay(500);}
