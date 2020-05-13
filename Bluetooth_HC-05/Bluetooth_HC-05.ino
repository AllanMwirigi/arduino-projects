
#define led 13
String inputString="";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(led, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  if(Serial.available()){
    while(Serial.available()){
        char inChar = (char)Serial.read(); //read the input
        inputString += inChar;        //make a string of the characters coming on serial
     }
    Serial.println(inputString);  
    if(inputString == "a"){         //in case of 'a' turn the LED on
      digitalWrite(led, HIGH);  
    }else if(inputString == "b"){   //incase of 'b' turn the LED off
      digitalWrite(led, LOW);
    }
    inputString = "";
   }
}

void LEDOn()
{ 
  digitalWrite(led, HIGH);
}

void LEDOff()
{
  digitalWrite(led, LOW);
}
