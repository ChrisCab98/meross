/*
   MotionSensor.ino

    ESP8266-based MQTT
    PIR motion sensor for HomeKit

    First Created: 14.08.2017
    Last  Updated: 15.08.2017
    Created by: Amruth Pabba aka QuickPi
*/
char *ssid = "TP-Link_1526";                            //Wi-Fi AP Name
char *password = "00102698";                            //Wi-Fi Password
char *mqtt_server = "192.168.1.29";                     //MQTT Server IP
char *mqtt_name = "Christopher Bedroom Contact Sensor"; //MQTT device name
char *mqtt_topic = "ChristopherBedroomContactSensor";   //MQTT topic for communication
char *mqtt_ending = "/data";                            //MQTT subsection for communication

#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <PubSubClient.h>
WiFiClient mainESP;
PubSubClient MQTT(mainESP);

#define G1 12
#define G2 13
#define G3 14
#define G4 16

char stateG1[4] = "OFF";

char stateG2[4] = "OFF";

char stateG3[4] = "OFF";

char stateG4[4] = "OFF";

char *mqtt_subtopic = "/data"; //MQTT topic for communication
char *mqtt_maintopic = mqtt_topic;

void setup()
{

    pinMode(G1, OUTPUT);
    digitalWrite(G1, LOW);

    pinMode(G2, OUTPUT);
    digitalWrite(G2, LOW);

    pinMode(G3, OUTPUT);
    digitalWrite(G3, LOW);

    pinMode(G4, OUTPUT);
    digitalWrite(G4, LOW);

    Serial.begin(115200);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.println("Connecting to WiFi..");
    }
    Serial.println("Connected to the WiFi network");

    MQTT.setServer(mqtt_server, 1883);
    MQTT.setCallback(callback);

    while (!MQTT.connected())
    {
        Serial.println("Connecting to MQTT...");

        if (MQTT.connect("ESP32Client"))
        {

            Serial.println("connected");
        }
        else
        {

            Serial.print("failed with state ");
            Serial.print(MQTT.state());
            delay(2000);
        }
    }

    MQTT.subscribe("cmnd/smartSurgeOutlet1/power");
    Serial.println("Sub to Outlet1");
    MQTT.subscribe("cmnd/smartSurgeOutlet2/power");
    Serial.println("Sub to Outlet2");
    MQTT.subscribe("cmnd/smartSurgeOutlet3/power");
    Serial.println("Sub to Outlet3");
    MQTT.subscribe("cmnd/smartSurgeOutlet4/power");
    Serial.println("Sub to Outlet4");
}

void loop()
{
    MQTT.loop();
}

void callback(char *topic, byte *payload, unsigned int length)
{
    char msg[4];
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("] ");

    if (strcmp(topic, "cmnd/smartSurgeOutlet1/power") == 0)
    {

        Serial.println("New Event On Outlet1 !");

        for (int i = 0; i < length; i++)
        {
            Serial.print((char)payload[i]);
            msg[i] = (char)payload[i];
        }
        Serial.println();
        Serial.println(msg);

        if (msg[0] == 'o' && msg[1] == 'n')
        {
            Serial.println("LED ON");
            stateG1[0] = 'O';
            stateG1[1] = 'N';
            stateG1[2] = '\0';
            MQTT.publish("stat/smartSurgeOutlet1/POWER", stateG1);
            digitalWrite(G1, HIGH);
        }

        if (msg[0] == 'o' && msg[1] == 'f' && msg[2] == 'f')
        {
            Serial.println("LED OFF");
            stateG1[0] = 'O';
            stateG1[1] = 'F';
            stateG1[2] = 'F';
            stateG1[3] = '\0';
            MQTT.publish("stat/smartSurgeOutlet1/POWER", stateG1);
            digitalWrite(G1, LOW);
        }

        if (length == 0)
        {
            Serial.println("IOS Check stat");
            Serial.println(stateG1);
            MQTT.publish("stat/smartSurgeOutlet1/POWER", stateG1);
        }
    }

    if (strcmp(topic, "cmnd/smartSurgeOutlet2/power") == 0)
    {

        Serial.println("New Event On Outlet2 !");

        for (int i = 0; i < length; i++)
        {
            Serial.print((char)payload[i]);
            msg[i] = (char)payload[i];
        }
        Serial.println();
        Serial.println(msg);

        if (msg[0] == 'o' && msg[1] == 'n')
        {
            Serial.println("LED ON");
            stateG2[0] = 'O';
            stateG2[1] = 'N';
            stateG2[2] = '\0';
            MQTT.publish("stat/smartSurgeOutlet2/POWER", stateG2);
            digitalWrite(G2, HIGH);
        }

        if (msg[0] == 'o' && msg[1] == 'f' && msg[2] == 'f')
        {
            Serial.println("LED OFF");
            stateG2[0] = 'O';
            stateG2[1] = 'F';
            stateG2[2] = 'F';
            stateG2[3] = '\0';
            MQTT.publish("stat/smartSurgeOutlet2/POWER", stateG2);
            digitalWrite(G2, LOW);
        }

        if (length == 0)
        {
            Serial.println("IOS Check stat");
            Serial.println(stateG2);
            MQTT.publish("stat/smartSurgeOutlet2/POWER", stateG2);
        }
    }

    if (strcmp(topic, "cmnd/smartSurgeOutlet3/power") == 0)
    {

        Serial.println("New Event On Outlet3 !");

        for (int i = 0; i < length; i++)
        {
            Serial.print((char)payload[i]);
            msg[i] = (char)payload[i];
        }
        Serial.println();
        Serial.println(msg);

        if (msg[0] == 'o' && msg[1] == 'n')
        {
            Serial.println("LED ON");
            stateG3[0] = 'O';
            stateG3[1] = 'N';
            stateG3[2] = '\0';
            MQTT.publish("stat/smartSurgeOutlet3/POWER", stateG3);
            digitalWrite(G3, HIGH);
        }

        if (msg[0] == 'o' && msg[1] == 'f' && msg[2] == 'f')
        {
            Serial.println("LED OFF");
            stateG3[0] = 'O';
            stateG3[1] = 'F';
            stateG3[2] = 'F';
            stateG3[3] = '\0';
            MQTT.publish("stat/smartSurgeOutlet3/POWER", stateG3);
            digitalWrite(G3, LOW);
        }

        if (length == 0)
        {
            Serial.println("IOS Check stat");
            Serial.println(stateG3);
            MQTT.publish("stat/smartSurgeOutlet3/POWER", stateG3);
        }
    }

    if (strcmp(topic, "cmnd/smartSurgeOutlet4/power") == 0)
    {

        Serial.println("New Event On Outlet4 !");

        for (int i = 0; i < length; i++)
        {
            Serial.print((char)payload[i]);
            msg[i] = (char)payload[i];
        }
        Serial.println();
        Serial.println(msg);

        if (msg[0] == 'o' && msg[1] == 'n')
        {
            Serial.println("LED ON");
            stateG4[0] = 'O';
            stateG4[1] = 'N';
            stateG4[2] = '\0';
            MQTT.publish("stat/smartSurgeOutlet4/POWER", stateG4);
            digitalWrite(G4, HIGH);
        }

        if (msg[0] == 'o' && msg[1] == 'f' && msg[2] == 'f')
        {
            Serial.println("LED OFF");
            stateG4[0] = 'O';
            stateG4[1] = 'F';
            stateG4[2] = 'F';
            stateG4[3] = '\0';
            MQTT.publish("stat/smartSurgeOutlet4/POWER", stateG4);
            digitalWrite(G4, LOW);
        }

        if (length == 0)
        {
            Serial.println("IOS Check stat");
            Serial.println(stateG4);
            MQTT.publish("stat/smartSurgeOutlet4/POWER", stateG4);
        }
    }
}

void reconnect()
{
    while (!MQTT.connected())
    {
        Serial.print("Attempting MQTT connection...");
        if (MQTT.connect(mqtt_name))
        {
            Serial.println("connected");
        }
        else
        {
            Serial.print("failed, rc=");
            Serial.print(MQTT.state());
            Serial.println(" try again in 5 seconds");
            for (int i = 0; i < 5000; i++)
            {
                delay(1);
            }
        }
    }
}

void startWiFi()
{
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    while (WiFi.waitForConnectResult() != WL_CONNECTED)
    {
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
