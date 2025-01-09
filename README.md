
# DHT11 温湿度采集与发送项目

## 简介

本项目使用 ESP8266 和 DHT11 传感器采集温湿度数据，并通过以下方式发送：  
- **MQTT**：将温湿度数据发送到指定的 MQTT 服务器主题；  
- **HTTP PUT**：通过 HTTP 请求将温湿度数据上传至 Home Assistant 或其他 REST API 服务器。


---

## 使用方法

### 1. 硬件准备  
- 一块 ESP8266 开发板（如 NodeMCU）。  
- 一个 DHT11 温湿度传感器（或兼容的 DHT22）。  
- 根据开发板的引脚图连接 DHT 传感器数据线至指定 GPIO（默认使用 D2 引脚）。  

### 2. 软件准备  
- 确保 Arduino IDE 已安装以下库：  
  - [DHT sensor library](https://github.com/adafruit/DHT-sensor-library)  
  - [PubSubClient](https://github.com/knolleary/pubsubclient)  
  - [ESP8266HTTPClient](https://arduino-esp8266.readthedocs.io/en/latest/)  

### 3. 配置文件

#### WiFi 配置  
打开 `main.ino` 文件，修改 WiFi 名称和密码：  
```cpp
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";
```

#### MQTT 配置  
打开 `mqtt_sender.cpp`，修改以下内容：  
```cpp
const char* mqtt_server = "YOUR_MQTT_SERVER";
const int mqtt_port = YOUR_MQTT_PORT;  // 通常是 1883
const char* mqtt_topic_temp = "home/sensor/temperature";
const char* mqtt_topic_humidity = "home/sensor/humidity";
```

#### HTTP POST 配置  
打开 `http_sender.cpp`，修改以下内容：  
```cpp
const char* hass_url_temp = "https://YOUR_HASS_URL/api/states/sensor.dht_temperature";
const char* hass_url_humidity = "https://YOUR_HASS_URL/api/states/sensor.dht_humidity";
const char* hass_token = "YOUR_HASS_TOKEN";
```

### 4. 启用发送方式  
在 `main.ino` 的 `loop()` 函数中，根据需要启用 MQTT 或 HTTP 的数据发送：  
- **启用 MQTT**：调用 `sendMQTTTemperature()` 和 `sendMQTTHumidity()`。  
- **启用 HTTP POST**：调用 `sendHTTPTemperature()` 和 `sendHTTPHumidity()`。  
- **同时启用**：无需修改，保留所有函数调用即可。  

例如，只使用 HTTP POST，可以将 MQTT 函数注释掉：  
```cpp
void loop() {
  float temperature = readTemperature();
  float humidity = readHumidity();

  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
    delay(5000);
    return;
  }

  sendHTTPTemperature(temperature);
  sendHTTPHumidity(humidity);

  delay(10000);  // 每 10 秒循环一次
}
```

### 5. 上传代码  
将代码上传到 ESP8266 开发板，打开串口监视器（波特率 115200），观察 WiFi 连接和数据发送的日志输出。

---

## 文件结构

```
项目目录
├── main.ino               主程序，负责调用各模块
├── dht_sensor.h/.cpp      DHT 传感器模块
│   ├── 初始化传感器
│   ├── 读取温度数据
│   └── 读取湿度数据
├── mqtt_sender.h/.cpp     MQTT 发送模块
│   ├── 初始化 MQTT 连接
│   ├── 发送温度数据到指定主题
│   └── 发送湿度数据到指定主题
├── http_sender.h/.cpp     HTTP PUT 发送模块
    ├── 初始化 HTTP 发送
    ├── 发送温度数据到 Home Assistant
    └── 发送湿度数据到 Home Assistant
```

---

## 注意事项

1. **WiFi 稳定性**：确保设备连接的 WiFi 信号稳定，避免频繁掉线导致数据发送失败。  
2. **发送间隔**：`main.ino` 中的 `delay(10000)` 设置了 10 秒的数据发送间隔，可根据需求调整（建议不要过于频繁）。  
3. **证书校验**：如果 HTTP URL 使用 HTTPS 协议，请确保正确配置证书，或在代码中忽略证书校验。  
4. **MQTT 和 HTTP 选择**：可根据实际需求选择启用 MQTT、HTTP 或两者同时使用。  

---

## 示例日志

运行代码后，打开串口监视器，将看到类似如下输出：  
```
Connecting to Wi-Fi....
Wi-Fi connected.
Temperature: 25.4 °C
Humidity: 60.2 %
Temperature sent via MQTT.
Humidity sent via MQTT.
Temperature HTTP Response code: 200
Humidity HTTP Response code: 200
```
