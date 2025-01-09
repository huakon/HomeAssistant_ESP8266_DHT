#include "mqtt_sender.h"
#include <PubSubClient.h>
#include <ESP8266WiFi.h>

// MQTT 配置
const char* mqtt_server = "mqtt.example.com";
const int mqtt_port = 1883;
const char* mqtt_topic_temp = "home/sensor/temperature";
const char* mqtt_topic_humidity = "home/sensor/humidity";

// MQTT 客户端
WiFiClient espClient;
PubSubClient mqttClient(espClient);

void initMQTTSender() {
  mqttClient.setServer(mqtt_server, mqtt_port);
}

void sendMQTTTemperature(float temperature) {
  if (mqttClient.connected() || mqttClient.connect("ESP8266_Client")) {
    mqttClient.publish(mqtt_topic_temp, String(temperature).c_str());
    Serial.println("Temperature sent via MQTT.");
  } else {
    Serial.println("Failed to connect to MQTT server for temperature.");
  }
}

void sendMQTTHumidity(float humidity) {
  if (mqttClient.connected() || mqttClient.connect("ESP8266_Client")) {
    mqttClient.publish(mqtt_topic_humidity, String(humidity).c_str());
    Serial.println("Humidity sent via MQTT.");
  } else {
    Serial.println("Failed to connect to MQTT server for humidity.");
  }
}
