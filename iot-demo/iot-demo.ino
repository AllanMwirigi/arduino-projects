#include <PubSubClient.h>
#include <ESP8266WiFi.h>

//https://www.emqx.com/en/blog/esp8266-connects-to-the-public-mqtt-broker

const char* WIFI_SSID = "FAiba4G-AM";
const char* WIFI_PASSWORD = "7FJGWJ8u8Nam";
//const char* mqttServer = "broker.hivemq.com";
//const int mqttPort = 8000;
const char* mqttServer = "broker.emqx.io";
const int mqttPort = 1883;
const char* mqttUser = "iotdemo";
const char* mqttPassword = "iotdemo";
//const char* mqttUser = "emqx";
//const char* mqttPassword = "public";
const char* pubTopic = "iotdemo/web";
const char* subTopic = "iotdemo/nodemcu";

const int trigPin = 2;  //D4
const int echoPin = 0;  //D3

WiFiClient espClient;
PubSubClient mqttClient(espClient);

void setup() {
  // put your setup code here, to run once:
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID,WIFI_PASSWORD);
  while ( WiFi.status() != WL_CONNECTED ) {
    Serial.println("WIFI NOT CONNECTED");
    delay(500);
  }
  Serial.println("WIFI CONNECTED");

  mqttClient.setServer(mqttServer, mqttPort);
  mqttClient.setCallback(mqttCallback);
  
  while (!mqttClient.connected()) {
        Serial.println("Connecting to MQTT...");
        String client_id = "esp8266-client-";
        client_id += String(WiFi.macAddress());
    
        if (mqttClient.connect(client_id.c_str(), mqttUser, mqttPassword )) {
//        if (mqttClient.connect("ESP8266Client")) {

            Serial.println("mqtt connected");  

        } else {

            Serial.print("mqtt failed to connect with state ");
            Serial.println(mqttClient.state());
            delay(2000);

        }
    }

    mqttClient.subscribe(subTopic);
}

void loop() {
  // put your main code here, to run repeatedly:
  mqttClient.loop();

  findDistance();
  
  delay(5000);

  // print a random number from 10 to 19
//    int  randNumber = random(1, 20);
//    String str = String(randNumber);
//    char charBuf[3];
//    str.toCharArray(charBuf, 3);
//  mqttClient.publish(pubTopic, charBuf);
//  delay(10000);

}

void findDistance() {
  // Clears the trigPin condition
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  long duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  int distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)

  String str = String(distance);
  str += " cm";
  char data[10];
  str.toCharArray(data, 10);
  mqttClient.publish(pubTopic, data);
  
  // Displays the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
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
