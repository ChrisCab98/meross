/*
   MotionSensor.ino

    ESP8266-based MQTT
    PIR motion sensor for HomeKit

    First Created: 14.08.2017
    Last  Updated: 15.08.2017
    Created by: Amruth Pabba aka QuickPi
*/
char* ssid = "TP-Link_1526"; //Wi-Fi AP Name
char* password = "00102698"; //Wi-Fi Password
char* mqtt_server = "192.168.1.49"; //MQTT Server IP
char* mqtt_name = "Christopher Bedroom Contact Sensor"; //MQTT device name
char* mqtt_topic = "ChristopherBedroomContactSensor"; //MQTT topic for communication
char* mqtt_ending = "/data"; //MQTT subsection for communication

#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <PubSubClient.h>
WiFiClient mainESP;
PubSubClient MQTT(mainESP);

char state[4] = "OFF";

char* mqtt_subtopic = "/data"; //MQTT topic for communication
char* mqtt_maintopic = mqtt_topic;

void setup() {

  pinMode(2,OUTPUT);
  digitalWrite(2,LOW);
 
  Serial.begin(115200);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
 
  MQTT.setServer(mqtt_server, 1883);
  MQTT.setCallback(callback);
 
  while (!MQTT.connected()) {
    Serial.println("Connecting to MQTT...");
 
    if (MQTT.connect("ESP32Client")) {
 
      Serial.println("connected");  
 
    } else {
 
      Serial.print("failed with state ");
      Serial.print(MQTT.state());
      delay(2000);
 
    }
  }
 
  MQTT.subscribe("cmnd/smartSurgeOutlet1/power");
 
}

void loop() {
  MQTT.loop();
}

void callback(char* topic, byte* payload, unsigned int length) {
  char msg[4];
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
    msg[i] = (char)payload[i];
  }
  Serial.println();
  Serial.println(msg);
  
  if (msg[0] == 'o' && msg[1] == 'n')
    {
      Serial.println("LED ON");
      state[0] = 'O';
      state[1] = 'N';
      state[2] = '\0';
      MQTT.publish("stat/smartSurgeOutlet1/POWER",state);
      digitalWrite(2,HIGH);  
    }

    
  if (msg[0] == 'o' && msg[1] == 'f' && msg[2] == 'f')
  {
    Serial.println("LED OFF");
    state[0] = 'O';
    state[1] = 'F';
    state[2] = 'F';
    state[3] = '\0';
    MQTT.publish("stat/smartSurgeOutlet1/POWER",state);
    digitalWrite(2,LOW);
  }


    if (length == 0)
  {
    Serial.println("IOS Check stat");
    Serial.println(state); 
    MQTT.publish("stat/smartSurgeOutlet1/POWER",state);
  }
  
}

void reconnect() {
  while (!MQTT.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (MQTT.connect(mqtt_name)) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(MQTT.state());
      Serial.println(" try again in 5 seconds");
      for (int i = 0; i < 5000; i++) {
        delay(1);
      }
    }
  }
}

void startWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed! Rebooting...");
    delay(1000);
    ESP.restart();
  }
  WiFi.hostname(mqtt_name);
  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  MQTT.setServer(mqtt_server, 1883);
  MQTT.setCallback(callback);
}
