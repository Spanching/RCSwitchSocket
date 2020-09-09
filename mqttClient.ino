#include <PubSubClient.h>
#include <WiFiClient.h>
#include "config.h";

void enableRCDeskSocket();
void disableRCDeskSocket();

WiFiClient espClient;

PubSubClient client(espClient);

char* topic_pc = "home/bedroom/ultrazaziki/power";
char* topic_desk = "home/bedroom/desk";
char* topic_rcsocket = "home/bedroom/rcsocket";

char* username = MQTT_USER;
char* password = MQTT_PASSWORD;

void setup_mqtt(){
  char * server = "192.168.0.20";
  client.setServer(server, 1883);
  client.setCallback(callback);
  Serial.print("Setup Mqtt with server");
  Serial.println(server);
}

void loop_mqtt(){
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}

void handlePCOnMessage() {
  enableRCDeskSocket();
  delay(5000);
  client.publish(topic_pc, "1");
}
void handlePCOffMessage() {
  client.publish(topic_pc, "0");
}

void callback(char* topic, byte* payload, unsigned int length) {
  char* back_topic = (char*)malloc(200);
  memset(back_topic, '\0', 200);
  strcpy(back_topic, topic);
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  String str_payload = "";
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
    str_payload += (char)payload[i]; 
  }
  Serial.println();
  if (strcmp(topic, topic_desk)==0){
    if (str_payload.toInt() == 1) {
      handlePCOnMessage();
    } else if (str_payload.toInt() == 0) {
      handlePCOffMessage();
    }
  }
  if (strcmp(topic, topic_rcsocket)==0){
    if (str_payload.toInt() == 1) {
      enableRCDeskSocket();
    } else if (str_payload.toInt() == 0) {
      disableRCDeskSocket();
    }
  }
  
  char* tmp = (char*)malloc(length+1);
  strcat(back_topic, "/back");
  Serial.print(back_topic);
  Serial.println(":  " + str_payload);
  str_payload.toCharArray(tmp, length+1);
  client.publish(back_topic, tmp);
  free(tmp);
  free(back_topic);
}

void handleDeskOnAlexa() {
  client.publish("home/bedroom/desk/back", "1");  
}
void handleDeskOffAlexa() {
  client.publish("home/bedroom/desk/back", "0");  
}

void reconnect() {
  // Loop until we're re-/connected
  if (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str(), username, password)) {
      Serial.println("MQTT connected");
      client.subscribe(topic_desk);
      client.subscribe(topic_rcsocket);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in a couple seconds");
      // Wait 5 seconds before retrying
      delay(2500);
    }
  }
}
