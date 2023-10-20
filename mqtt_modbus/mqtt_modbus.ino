#include <WiFi.h>
#include <PubSubClient.h>
#include "ModbusRtu.h"
#include <ArduinoOTA.h>
#include <WiFiUdp.h>

// Update these with values suitable for your network.

Modbus slave(1, Serial1, 0);

const char* ssid = "MIC_2.4GHz";
const char* password = "999999999";
const char* mqtt_server = "192.168.100.98";


IPAddress local_IP(192,168,100,209);
IPAddress gateway(192,168,100,1);
IPAddress subnet(255,255,255,0);

WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE	(50)
char msg[MSG_BUFFER_SIZE];
int value = 0;


unsigned long timeread = 0;
unsigned int interval = 1000;

uint8_t state=0;
const int num = 6;
uint16_t Data[num];

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  //WiFi.mode(WIFI_STA);
  WiFi.config(local_IP, gateway, subnet);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  // Switch on the LED if an 1 was received as first character
  if ((char)payload[0] == '1') {
    digitalWrite(BUILTIN_LED, LOW);   // Turn the LED on (Note that LOW is the voltage level
    // but actually the LED is on; this is because
    // it is active low on the ESP-01)
  } else {
    digitalWrite(BUILTIN_LED, HIGH);  // Turn the LED off by making the voltage HIGH
  }

}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("outTopic", "hello world");
      // ... and resubscribe
      client.subscribe("inTopic");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
  pinMode(BUILTIN_LED, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
  Serial.begin(115200);
  Serial1.begin(115200);
  slave.start();
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {

  if (!client.connected()) {
    reconnect();
  }
  
  client.loop();{
  state = slave.poll(Data,num);
  unsigned long currentMillis = millis();
  if (currentMillis - timeread >= interval && state >= 7 )
  {
    timeread = currentMillis;
    Serial.println("-----------------------------");
    Serial.print("D200 : "); Serial.println(Data[0]);
    Serial.print("D201 : "); Serial.println(Data[1]);
    Serial.print("D202 : "); Serial.println(Data[2]);
    Serial.print("D203 : "); Serial.println(Data[3]);
    Serial.print("D204 : "); Serial.println(Data[4]);
    Serial.print("D205 : "); Serial.println(Data[5]);
    Serial.println("-----------------------------");
  
  }
    String d200 = String(Data[0]);
    client.publish("Topic1",d200.c_str());
   // delay(0);
    
    
  }
}