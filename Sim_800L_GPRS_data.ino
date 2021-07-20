#include <SoftwareSerial.h>
SoftwareSerial gprsSerial(11,10);
 

 

 
void setup()
{
  gprsSerial.begin(9600);               // the GPRS baud rate   
  Serial.begin(9600);    // the GPRS baud rate

}
 
void loop()
{
     
   
  if (gprsSerial.available())
    Serial.write(gprsSerial.read());
  
  gprsSerial.println("Initializing...");
  delay(2000);
  
  gprsSerial.println("AT");
  delay(1000);
 
  gprsSerial.println("AT+CPIN?");
  delay(1000);
 
  gprsSerial.println("AT+CREG?");
  delay(1000);
 
  gprsSerial.println("AT+CGATT?");
  delay(1000);
 
  gprsSerial.println("AT+CIPSHUT");
  delay(1000);
 
  gprsSerial.println("AT+CIPSTATUS");
  delay(1000);
 
  gprsSerial.println("AT+CIPMUX=0");
  delay(2000);
 
  ShowSerialData();
 
  gprsSerial.println("AT+CSTT=\"safaricom\"");//start task and setting the APN,
  delay(1000);
 
  ShowSerialData();
 
  gprsSerial.println("AT+CIICR");//bring up wireless connection
  delay(2000);
 
  ShowSerialData();
 
  gprsSerial.println("AT+CIFSR");//get local IP adress
  delay(2000);
   delay(3000);

  ShowSerialData();
 
  gprsSerial.println("AT+CIPSPRT=0");
 
  ShowSerialData();
  
  gprsSerial.println("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",\"80\"");//start up the connection
  delay(4000);
 
  ShowSerialData();
 
  gprsSerial.println("AT+CIPSEND");//begin send data to remote server
  delay(4000);
  ShowSerialData();
  
  String str="GET https://api.thingspeak.com/update?api_key=893UKZOX06KDIE0C&field1=35";
  Serial.println(str);
  gprsSerial.println(str);//begin send data to remote server
  
  delay(2000);
  ShowSerialData();
 
  gprsSerial.println((char)26);//sending
  delay(3000);//waitting for reply, important! the time is base on the condition of internet 
  gprsSerial.println();
 
  ShowSerialData();
 
  gprsSerial.println("AT+CIPSHUT");//close the connection
  delay(100);
  ShowSerialData();
} 
void ShowSerialData()
{
  while(gprsSerial.available()!=0)
  Serial.write(gprsSerial.read());
  delay(2000); 
  
}
