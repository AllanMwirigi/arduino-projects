int led=3;
int lightsensor=A1;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  pinMode(lightsensor, INPUT);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  int value = analogRead(lightsensor);
  Serial.println(value);
  int mappedvalue=map(value,0,800,255,0);
  analogWrite(led, mappedvalue);
  
  delay(10);
}
