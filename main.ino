#include "dht_sensor.h"
#include "mqtt_sender.h"
#include "config.h"
#include "http_sender.h"
#include <ESP8266WiFi.h>

void setup() {
  Serial.begin(115200);

  // 初始化 DHT 传感器
  initDHT();

  // 连接到 WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nWi-Fi connected.");

  // 初始化 MQTT 和 HTTP 发送模块
  initMQTTSender();
  initHTTPSender();
}

void loop() {
  // 读取传感器数据
  float temperature = readTemperature();
  float humidity = readHumidity();

  // 检查传感器数据是否有效
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
    delay(5000);
    return;
  }

  // 打印数据到串行监视器
  Serial.println("Temperature: " + String(temperature) + " °C");
  Serial.println("Humidity: " + String(humidity) + " %");

  // 通过 MQTT 发送数据
  sendMQTTTemperature(temperature);
  sendMQTTHumidity(humidity);

  // 通过 HTTP POST 发送数据
  sendHTTPTemperature(temperature);
  sendHTTPHumidity(humidity);

  delay(10000); // 每 10 秒循环一次
}
