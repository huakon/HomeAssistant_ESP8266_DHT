#include <ESP8266WiFi.h>       // ESP8266 Wi-Fi库
#include <ESP8266HTTPClient.h> // ESP8266 HTTP请求库
#include <DHT.h>               // DHT传感器库

// Wi-Fi 配置
const char* ssid = "YourWiFiSSID";       // Wi-Fi名称
const char* password = "YourWiFiPassword"; // Wi-Fi密码

// Home Assistant 配置
const char* hass_url = "https://YourHomeAssistantURL/api/states/"; // Home Assistant API URL
const char* hass_token = "YourAccessToken"; // Home Assistant长效访问令牌

// DHT传感器配置
#define DHTPIN D2           // DHT传感器连接的GPIO引脚
#define DHTTYPE DHT11       // DHT传感器类型（DHT11或DHT22）
DHT dht(DHTPIN, DHTTYPE);   // 初始化DHT对象

/**
 * 初始化设置
 */
void setup() {
  Serial.begin(115200); // 初始化串行通信，波特率为115200
  dht.begin();          // 启动DHT传感器

  // 连接到Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);         // 每1秒检查一次连接状态
    Serial.println("Connecting to Wi-Fi...");
  }
  Serial.println("Wi-Fi connected!"); // Wi-Fi连接成功
}

/**
 * 主循环函数
 */
void loop() {
  // 读取温度和湿度
  float temperature = dht.readTemperature(); // 读取温度（单位：摄氏度）
  float humidity = dht.readHumidity();       // 读取湿度（单位：百分比）

  // 检查温度是否有效，发送到Home Assistant
  if (!isnan(temperature)) {
    sendToHASS("sensor.temperature", temperature, "°C", "Temperature Sensor");
  } else {
    Serial.println("Failed to read temperature data.");
  }

  // 检查湿度是否有效，发送到Home Assistant
  if (!isnan(humidity)) {
    sendToHASS("sensor.humidity", humidity, "%", "Humidity Sensor");
  } else {
    Serial.println("Failed to read humidity data.");
  }

  delay(5000); // 等待5秒后再次读取
}

/**
 * 将数据发送到Home Assistant
 * @param entity_id   Home Assistant实体ID（如 "sensor.temperature"）
 * @param value       要发送的传感器数据值
 * @param unit        数据的单位（如 "°C" 或 "%"）
 * @param friendly_name 传感器的友好名称（如 "Temperature Sensor"）
 */
void sendToHASS(String entity_id, float value, String unit, String friendly_name) {
  // 确认Wi-Fi连接状态
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http; // 创建HTTP客户端对象

    // 拼接完整URL
    String url = String(hass_url) + entity_id;
    // 构建JSON负载
    String payload = "{\"state\": \"" + String(value) + 
                     "\", \"attributes\": {\"unit_of_measurement\": \"" + unit + 
                     "\", \"friendly_name\": \"" + friendly_name + "\"}}";

    http.begin(url); // 初始化HTTP连接
    // 添加请求头，包括认证信息和内容类型
    http.addHeader("Authorization", "Bearer " + String(hass_token));
    http.addHeader("Content-Type", "application/json");

    // 发送PUT请求到Home Assistant
    int httpResponseCode = http.PUT(payload);

    // 根据响应代码输出日志
    if (httpResponseCode > 0) {
      Serial.printf("HTTP Response code for %s: %d\n", entity_id.c_str(), httpResponseCode);
    } else {
      Serial.printf("Error sending %s, HTTP code: %d\n", entity_id.c_str(), httpResponseCode);
    }

    // 结束HTTP连接
    http.end();
  } else {
    Serial.println("Wi-Fi not connected. Cannot send data to Home Assistant.");
  }
}
