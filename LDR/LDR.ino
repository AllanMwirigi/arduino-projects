int LED=13;
int LDR=A2;


void setup() {
  // put your setup code here, to run once:
pinMode(LED,OUTPUT);
pinMode(LDR,INPUT);
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
int value=analogRead(LDR);
Serial.println(value);
if(value<300){
 digitalWrite( LED,HIGH);
 }
 else{
  digitalWrite(LED,LOW);
  }
 
  
delay(500);

}
