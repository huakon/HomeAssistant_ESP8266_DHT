#include "http_sender.h"
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>

// 初始化 WiFiClientSecure
WiFiClientSecure client;

// Home Assistant API 配置
const char* hass_url_temp = "https://your_home_assistant_url/api/states/sensor.dht_temperature";
const char* hass_url_humidity = "https://your_home_assistant_url/api/states/sensor.dht_humidity";
const char* hass_token = "YOUR_HASS_TOKEN";  // 请替换为您自己的 Home Assistant Token

// 选择是否跳过证书验证 (仅用于调试)
bool skipCertificateVerification = true;  // 设置为 true 跳过证书验证

// 跳过证书验证
void setupInsecureConnection() {
  client.setInsecure();  // 跳过证书验证，仅用于调试
}

// 验证证书
void setupSecureConnection() {
  // 设置根证书 (如果你想验证证书，可以把证书字符串填在这里)
  const char* rootCACertificate = \
    "-----BEGIN CERTIFICATE-----\n" \
    "MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEA7kHRAL3hSg9mRqqz5W50\n" \
    "...省略证书...\n" \
    "-----END CERTIFICATE-----\n";
  
  client.setTrustAnchors(new X509List(rootCACertificate));  // 设置根证书
}

// HTTP POST 发送数据
void sendHTTPData(float temperature, float humidity) {
  HTTPClient http;

  // 根据配置，选择是否跳过证书验证
  if (skipCertificateVerification) {
    setupInsecureConnection();  // 跳过证书验证
  } else {
    setupSecureConnection();  // 启用证书验证
  }

  // 发送温度数据
  http.begin(client, hass_url_temp);  // 使用 HTTPS 协议
  http.addHeader("Authorization", "Bearer " + String(hass_token));
  http.addHeader("Content-Type", "application/json");
  String tempPayload = "{\"state\": \"" + String(temperature) + "\", \"attributes\": {\"unit_of_measurement\": \"°C\", \"friendly_name\": \"DHT Temperature\"}}";
  int httpResponseCode = http.POST(tempPayload);  // 使用 POST 发送数据
  if (httpResponseCode > 0) {
    Serial.println("Temperature HTTP POST Success: " + String(httpResponseCode));
  } else {
    Serial.println("Temperature HTTP POST Failed: " + String(httpResponseCode));
  }
  http.end();

  // 发送湿度数据
  http.begin(client, hass_url_humidity);  // 使用 HTTPS 协议
  http.addHeader("Authorization", "Bearer " + String(hass_token));
  http.addHeader("Content-Type", "application/json");
  String humidityPayload = "{\"state\": \"" + String(humidity) + "\", \"attributes\": {\"unit_of_measurement\": \"%\", \"friendly_name\": \"DHT Humidity\"}}";
  httpResponseCode = http.POST(humidityPayload);  // 使用 POST 发送数据
  if (httpResponseCode > 0) {
    Serial.println("Humidity HTTP POST Success: " + String(httpResponseCode));
  } else {
    Serial.println("Humidity HTTP POST Failed: " + String(httpResponseCode));
  }
  http.end();
}
