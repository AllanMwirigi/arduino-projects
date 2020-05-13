#include <LiquidCrystal.h>
#include <SoftwareSerial.h>





//Create software serial object to communicate with SIM800L
SoftwareSerial mySerial(3, 2); //SIM800L Tx & Rx is connected to Arduino #3 & #2
LiquidCrystal lcd(12,11,5,4,6,7);

const byte numChars = 32;
char receivedChars[numChars]; // an array to store the received data

boolean newData = false;

char incomingMessage;
String msg="";
String row1="", row2="";
void setup()
{

  

  //Begin serial communication with Arduino and Arduino IDE (Serial Monitor)
  Serial.begin(9600);
  
  //Begin serial communication with Arduino and SIM800L
  mySerial.begin(9600);

  lcd.begin(16,2);

  Serial.println("Initializing..."); 
  delay(1000);

 // mySerial.println("AT"); //Once the handshake test is successful, it will back to OK
 // updateSerial();
  
  mySerial.println("AT+CMGF=1"); // Configuring TEXT mode
 // updateSerial();
  mySerial.println("AT+CNMI=1,2,0,0,0"); // Decides how newly arrived SMS messages should be handled
 // updateSerial();

 
}

void loop()
{
  updateSerial();

  if(msg.length() != 0){
      lcd.clear();
      lcd.setCursor(0, 0);
      //lcd.print("Data ");
      //lcd.setCursor(0, 1);
      lcd.print(row1);
      lcd.setCursor(0,1);
      lcd.print(row2);
  }
  
//  if(msg.length() != 0){
//    lcd.clear();
//    if(msg.length() <= 32){
//      lcd.setCursor(0, 0);
//      //lcd.print("Data ");
//      //lcd.setCursor(0, 1);
//      lcd.print(row1);
//      lcd.setCursor(0,1);
//      lcd.print(row2);
//    }
//    else{
//      lcd.setCursor(0, 0);
//      lcd.print(msg);
//      for (int positionCounter = 0; positionCounter < (msg.length()-16); positionCounter++) {
//        // scroll one position left:
//        lcd.scrollDisplayLeft();
//        // wait a bit:
//        delay(500);
//      }
//      for (int positionCounter = 0; positionCounter < (msg.length()+16); positionCounter++) {
//        // scroll one position left:
//        lcd.scrollDisplayRight();
//        // wait a bit:
//        delay(500);
//      }
//      for (int positionCounter = 0; positionCounter < 16; positionCounter++) {
//        // scroll one position left:
//        lcd.scrollDisplayLeft();
//        // wait a bit:
//        delay(500);
//      }
//    }
//    
//  }
  
}

void updateSerial()
{

   
 
  delay(500);
  while (Serial.available()) 
  {
   mySerial.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while(mySerial.available()) 
  {
    
    
   // incomingMessage = mySerial.read();
    //Serial.write(mySerial.read());//Forward what Software Serial received to Serial Port
  //Serial.println(mySerial.readString());
  String fullmsg = mySerial.readString();
  if(fullmsg.length() > 50){
    msg = fullmsg.substring(50);
    msg.trim();
    row1 = msg.substring(0, 16);
    row2 = msg.substring(16, 32);
    Serial.println(msg);
  }
  
  
    //delay(1000);
  }
}

/*
  void updateSerial()
{

  delay(500);
  while (Serial.available())
  {
    mySerial.write(Serial.read());//Forward what Serial received to Software Serial Port

  }
  while (mySerial.available())
  {
    //Serial.write(mySerial.read());
    String sms = mySerial.readString();
    Serial.println(sms);
    int index = sms.indexOf(';');
    String message = sms.substring(index);
    Serial.println("Message is :" + message );
     LiquidCrystal lcd(12,11,5,4,6,7);
    lcd.begin(16,2);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Data");
    lcd.setCursor(0, 1);
    lcd.print(message);

delay(1000);

  }
}



/*
void recvWithEndMarker() {
 static byte ndx = 0;
 char endMarker = '\n';
 char rc;
 
 // if (Serial.available() > 0) {
           while (Serial.available() > 0 && newData == false) {
 rc = Serial.read();
mySerial.write(rc);

 if (rc != endMarker) {
 receivedChars[ndx] = rc;
 ndx++;
 if (ndx >= numChars) {
 ndx = numChars - 1;
 }
 }
 else {
 receivedChars[ndx] = '\0'; // terminate the string

 
 ndx = 0;
 newData = true;
 }
 }

 while(mySerial.available()) 
  {
    
    incomingMessage = mySerial.read();
    Serial.write(incomingMessage);
}


void showNewData() {
 if (newData == true) {
 Serial.print("This just in ... ");
 Serial.println(receivedChars);
 newData = false;
 }
}*/
