#include "http_sender.h"
#include <ESP8266HTTPClient.h>

// Home Assistant 配置
const char* hass_url_temp = "https://.../api/states/sensor.dht_temperature";
const char* hass_url_humidity = "https://.../api/states/sensor.dht_humidity";
const char* hass_token = "YOUR_HASS_TOKEN";

void initHTTPSender() {
  // 如果需要初始化其他内容，可以在这里完成
}

void sendHTTPTemperature(float temperature) {
  HTTPClient http;
  http.begin(hass_url_temp);
  http.addHeader("Authorization", "Bearer " + String(hass_token));
  http.addHeader("Content-Type", "application/json");

  String payload = "{\"state\": \"" + String(temperature) + "\", \"attributes\": {\"unit_of_measurement\": \"°C\", \"friendly_name\": \"DHT Temperature\"}}";
  int httpResponseCode = http.PUT(payload);
  Serial.println("Temperature HTTP Response code: " + String(httpResponseCode));
  http.end();
}

void sendHTTPHumidity(float humidity) {
  HTTPClient http;
  http.begin(hass_url_humidity);
  http.addHeader("Authorization", "Bearer " + String(hass_token));
  http.addHeader("Content-Type", "application/json");

  String payload = "{\"state\": \"" + String(humidity) + "\", \"attributes\": {\"unit_of_measurement\": \"%\", \"friendly_name\": \"DHT Humidity\"}}";
  int httpResponseCode = http.PUT(payload);
  Serial.println("Humidity HTTP Response code: " + String(httpResponseCode));
  http.end();
}
