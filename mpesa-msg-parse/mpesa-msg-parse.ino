
String mpesaMsg = "DT85TH896H Confirmed.You have received Ksh3,500.00 from JOHN DOE 0701234567 on 31/7/13 at 6:43 PM New M-PESA balance is Ksh11,312.00. To reverse, forward this message to 456";
int startIndex = 42;

void setup() {
  Serial.begin(9600);
  parseMpesaMsg(mpesaMsg);

}

void loop() {
  // put your main code here, to run repeatedly:

}

void parseMpesaMsg(String fullMsg){
  fullMsg.trim();
  String prt1 = fullMsg.substring(startIndex);
  int pointIndex = prt1.indexOf('.');
  String prt2 = prt1.substring(0, pointIndex);
  
  int commaIndex = prt2.indexOf(',');
  if(commaIndex == -1){
    Serial.print("Value: "); Serial.println(prt2);
  }
  else{
    Serial.print("Value with comma: "); Serial.println(prt2);
    String a = prt2.substring(0, commaIndex);
    String b = prt2.substring(commaIndex+1);
    String value = a+b;
    Serial.print("Value without comma: "); Serial.println(value);
  }
}

