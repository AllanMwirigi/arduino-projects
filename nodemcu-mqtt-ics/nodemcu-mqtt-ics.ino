#include <PubSubClient.h>
#include <ESP8266WiFi.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Max72xxPanel.h>
#include <time.h>
#include <DHT.h>
#include <DHT_U.h>

int pinCS = D4; 
int Pwm1 = D1; //Nodemcu PWM pin 
int a0 = D0;
int a1 = D3;
int numberOfHorizontalDisplays = 4;
int numberOfVerticalDisplays   = 1;
char time_value[20];
int motorRunning = 0;
int motorSpeed = 700;

const char* WIFI_SSID = "MY_WIFI";
const char* WIFI_PASSWORD = "************";
const char* mqttServer = "m12.cloudmqtt.com";
const int mqttPort = 15080;
const char* mqttUser = "xxxxxxxx";
const char* mqttPassword = "xxxxxxxx";
const char* pubTopic = "ICsVDS/nodemcu";

const String COMMAND_MOTOR_OFF = "0";
const String COMMAND_MOTOR_ON = "1";
const String COMMAND_STOP_MSG = "3";
String mqttMsg = "";
String displayMsg = "";

// LED Matrix Pin -> ESP8266 Pin
// Vcc            -> 3v  (3V on NodeMCU 3V3 on WEMOS)
// Gnd            -> Gnd (G on NodeMCU)
// DIN            -> D7  (Same Pin for WEMOS)
// CS             -> D4  (Same Pin for WEMOS)
// CLK            -> D5  (Same Pin for WEMOS)

Max72xxPanel matrix = Max72xxPanel(pinCS, numberOfHorizontalDisplays, numberOfVerticalDisplays);
WiFiClient espClient;
PubSubClient mqttClient(espClient);

int wait = 32; // In milliseconds
//int wait = 100;

int spacer = 1;
int width  = 5 + spacer; // The font width is 5 pixels

int m;

#define DHTPIN D2          // D3

#define DHTTYPE DHT22     // DHT 11

DHT dht(DHTPIN, DHTTYPE);

String sTemp = "", sHum = "";
float fTemp, fHum;
int timeSinceLastRead = 0;

void setup() {
    Serial.begin(115200);
   pinMode(a0, OUTPUT);  
   pinMode(a1, OUTPUT);
   pinMode(Pwm1, OUTPUT);
    dht.begin();

    //  WiFi.begin("YOUR_SSID","YOUR_PASSWORD");
    WiFi.begin(WIFI_SSID,WIFI_PASSWORD);

    //CHANGE THE POOL WITH YOUR CITY. SEARCH AT https://www.ntppool.org/zone/@

    //configTime(0 * 3600, 0, "server 3.ke.pool.ntp.org", "server 3.africa.pool.ntp.org", "server 0.africa.pool.ntp.org");

    //  setenv("TZ", "GMT+3EAT",1);
    //setenv("TZ", "GMT-1BST",1);

    matrix.setIntensity(0); // Use a value between 0 and 15 for brightness
    matrix.setRotation(0, 1);    // The first display is position upside down
    matrix.setRotation(1, 1);    // The first display is position upside down
    matrix.setRotation(2, 1);    // The first display is position upside down
    matrix.setRotation(3, 1);    // The first display is position upside down
    matrix.fillScreen(LOW);
    matrix.write();

    while ( WiFi.status() != WL_CONNECTED ) {
        matrix.drawChar(2,0, 'W', HIGH,LOW,1); // H
        matrix.drawChar(8,0, 'I', HIGH,LOW,1); // HH  
        matrix.drawChar(14,0,'-', HIGH,LOW,1); // HH:
        matrix.drawChar(20,0,'F', HIGH,LOW,1); // HH:M
        matrix.drawChar(26,0,'I', HIGH,LOW,1); // HH:MM
        matrix.write(); // Send bitmap to display
        delay(250);
        matrix.fillScreen(LOW);
        matrix.write();
        delay(250);
    }

    mqttClient.setServer(mqttServer, mqttPort);
    mqttClient.setCallback(mqttCallback);

    while (!mqttClient.connected()) {
        Serial.println("Connecting to MQTT...");
    
        if (mqttClient.connect("ESP8266Client", mqttUser, mqttPassword )) {

            Serial.println("mqtt connected");  

        } else {

            Serial.print("mqtt failed with state ");
            Serial.print(mqttClient.state());
            delay(2000);

        }
    }

    // client.publish("ic-vds/test", "hello"); //Topic name
    mqttClient.subscribe(pubTopic);


}

void loop() {
    m = map(analogRead(0),0,1024,0,12);
    matrix.setIntensity(m);
    matrix.fillScreen(LOW);
    mqttClient.loop();

    

     if(timeSinceLastRead > 2000) {
       // Reading temperature or humidity takes about 250 milliseconds!
       // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
       fHum = dht.readHumidity();
       // Read temperature as Celsius (the default)
       fTemp = dht.readTemperature();
  
       // Check if any reads failed and exit early (to try again).
       if (isnan(fHum) || isnan(fTemp)) {
           Serial.println("Failed to read from DHT sensor!");
           timeSinceLastRead = 0;
           return;
       }
       if(fTemp > 28){
        analogWrite(Pwm1, motorSpeed);
        digitalWrite(a0, HIGH);
        digitalWrite(a1, LOW);
        motorRunning = 1;
       }
      if(mqttMsg != COMMAND_MOTOR_ON && mqttMsg != "" && fTemp < 28 && motorRunning == 1){
         digitalWrite(a0, LOW);
         motorRunning = 0;
      }
       
       timeSinceLastRead = 0;
     }
     sTemp = (String)(int)fTemp;
     sHum = (String)(int)fHum;
     //   String message = "Temp: "+sTemp+"C"+" Hum: "+sHum+"%"; //"Temp: 24.45'C Hum: 17.45%";
     String tempHum = "T:"+sTemp+",H:"+sHum; //"T:24,Hum:17";
     Serial.println(tempHum);
//     delay(100);
//     timeSinceLastRead += 100;
     

    if(mqttMsg == COMMAND_MOTOR_OFF){
       digitalWrite(a0, LOW);
       motorRunning = 0;
       mqttMsg = "";
    }
    if(mqttMsg == COMMAND_MOTOR_ON){
        analogWrite(Pwm1, motorSpeed);
        digitalWrite(a0, HIGH);
        digitalWrite(a1, LOW);
        motorRunning = 1;
    }
    if(displayMsg.length() > 0){
      displayMessage(displayMsg);
    }else{
      displayMessage(tempHum);
    }
}

    void displayMessage(String message){
    for ( int i = 0 ; i < width * message.length() + matrix.width() - spacer; i++ ) {
    //matrix.fillScreen(LOW);
    int letter = i / width;
    int x = (matrix.width() - 1) - i % width;
    int y = (matrix.height() - 8) / 2; // center the text vertically
    while ( x + width - spacer >= 0 && letter >= 0 ) {
        if ( letter < message.length() ) {
            matrix.drawChar(x, y, message[letter], HIGH, LOW, 1); // HIGH LOW means foreground ON, background off, reverse to invert the image
            }
            letter--;
            x -= width;
        }
        matrix.write(); // Send bitmap to display
        delay(wait/2);
        timeSinceLastRead += wait/2;
    }
}

void mqttCallback(char* topic, byte* payload, unsigned int length) {
    Serial.print("Message arrived in topic: ");
    Serial.println(topic);
    Serial.print("Message: ");
    String msg = "";
    for (int i = 0; i < length; i++) {
        //Serial.print((char)payload[i]);
        msg += (char)payload[i];
    }
    if(msg.length() > 1){
       displayMsg = msg;
    }else{
      if(msg == COMMAND_STOP_MSG){
        displayMsg = "";
      }else{
        mqttMsg = msg;
      }
      
    }
    Serial.print(mqttMsg);
    Serial.println();
    Serial.println("-----------------------");
}
