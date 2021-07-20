#include <PubSubClient.h>
#include <ESP8266WiFi.h>

const char* WIFI_SSID = "FF4392";
const char* WIFI_PASSWORD = "7FJGWJ8u8Nam";
const char* mqttServer = "broker.hivemq.com";
const int mqttPort = 8000;
const char* mqttUser = "xxxxxxxx";
const char* mqttPassword = "xxxxxxxx";
const char* pubTopic = "jkieee/web";
const char* subTopic = "jkieee/arduino";

WiFiClient espClient;
PubSubClient mqttClient(espClient);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID,WIFI_PASSWORD);
  while ( WiFi.status() != WL_CONNECTED ) {
    
  }

  mqttClient.setServer(mqttServer, mqttPort);
  mqttClient.setCallback(mqttCallback);
  
  while (!mqttClient.connected()) {
        Serial.println("Connecting to MQTT...");
    
//        if (mqttClient.connect("ESP8266Client", mqttUser, mqttPassword )) {
        if (mqttClient.connect("ESP8266Client")) {

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
  // put your main code here, to run repeatedly:
  mqttClient.loop();
  // print a random number from 10 to 19

  int  randNumber = random(1, 20);
    String str = String(randNumber);
    char charBuf[3];
    str.toCharArray(charBuf, 3);
  mqttClient.publish(pubTopic, charBuf);
  
  delay(3000);
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
    Serial.print(msg);
    Serial.println();
    Serial.println("-----------------------");
}
