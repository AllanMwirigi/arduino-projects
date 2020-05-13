
char command;
String string;
#define led 13

char junk;
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
    while (Serial.available() > 0){
      junk = Serial.read() ; 
    }      // clear the serial buffer
    
    if(inputString == "a"){         //in case of 'a' turn the LED on
      digitalWrite(led, HIGH);  
    }else if(inputString == "b"){   //incase of 'b' turn the LED off
      digitalWrite(led, LOW);
    }
    inputString = "";
  }


  
//if (Serial.available() > 0)
//  {string = "";}    
//   while(Serial.available() > 0)
//    {
//     command = ((byte)Serial.read());
//     if(command == ':')
//     {
//  break;
//     }
//     else
//      {
//        string += command;
//     }
//      delay(1);
//   } 
//    if(string == "LO")
//    {
//      LEDOn();
//    }   
//    if(string =="LF")
//    {
//      LEDOff();
//    }
}

void LEDOn()
{ 
  digitalWrite(led, HIGH);
}

void LEDOff()
{
  digitalWrite(led, LOW);
}
