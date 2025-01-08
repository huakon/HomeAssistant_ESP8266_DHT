
# **ESP8266 发送传感器数据到 Home Assistant**

这是一个使用 ESP8266 和 DHT 传感器，将温度和湿度数据发送到 Home Assistant 的示例项目。通过此代码，你可以将任何传感器数据实时上传到 Home Assistant，实现智能家居数据集成。

---

## **功能介绍**

- 读取 DHT11/DHT22 传感器数据（温度和湿度）。
- 使用 ESP8266 通过 Wi-Fi 连接到 Home Assistant。
- 通过 HTTP RESTful API，将数据发送到 Home Assistant。
- 支持 JSON 数据格式，包含状态和传感器属性。
- 可扩展至其他传感器。

---

## **硬件需求**

1. **ESP8266 开发板**（如 NodeMCU 或 Wemos D1 Mini）。
2. **DHT11 或 DHT22 温湿度传感器**。
3. 跳线和面包板。

---

## **接线说明**

| **DHT 引脚** | **ESP8266 引脚** |
| ------------ | ---------------- |
| VCC          | 3V3              |
| GND          | GND              |
| DATA         | D2               |

---

## **软件需求**

1. **Arduino IDE**。
2. ESP8266 开发板支持包（通过 Arduino IDE 添加）。
3. 以下 Arduino 库：
   - **DHT sensor library**（由 Adafruit 提供）。
   - **ESP8266WiFi**。
   - **ESP8266HTTPClient**。

---

## **代码说明**

1. **Wi-Fi 配置**
   ```cpp
   const char* ssid = "YourWiFiSSID";       // Wi-Fi名称
   const char* password = "YourWiFiPassword"; // Wi-Fi密码
   ```
   修改为你的 Wi-Fi SSID 和密码。

2. **Home Assistant 配置**
   ```cpp
   const char* hass_url = "https://YourHomeAssistantURL/api/states/";
   const char* hass_token = "YourAccessToken";
   ```
   替换为你的 Home Assistant API URL 和长效访问令牌。

3. **DHT 传感器设置**
   ```cpp
   #define DHTPIN D2
   #define DHTTYPE DHT11
   ```
   根据实际使用的 DHT 型号进行修改（如 DHT22）。

4. **发送数据到 Home Assistant**
   ```cpp
   sendToHASS("sensor.temperature", temperature, "°C", "Temperature Sensor");
   sendToHASS("sensor.humidity", humidity, "%", "Humidity Sensor");
   ```
   每个传感器对应一个实体 ID，需确保在 Home Assistant 中唯一。

---

## **运行步骤**

1. 打开 Arduino IDE，将代码上传到 ESP8266。
2. 确保 Home Assistant 已启用 API 并生成长效访问令牌。
3. 确保 ESP8266 与 Home Assistant 运行在同一网络下。
4. 在 Home Assistant 的开发者工具中查看新创建的实体，确认数据是否上传成功。

---

## **HTTP 响应代码**

- **200 OK**：请求成功，数据已成功发送并更新。
- **400 Bad Request**：请求格式错误，通常是 JSON 格式问题。
- **401 Unauthorized**：认证失败，检查 Token 或权限。
- **405 Method Not Allowed**：请求方法错误，应确保使用 PUT。
- **500 Internal Server Error**：Home Assistant 服务端发生错误。

---

## **扩展功能**

- 将更多传感器集成到代码中（如光照传感器、气压传感器）。
- 优化网络连接的稳定性和错误处理逻辑。
- 通过 MQTT 替代 HTTP 实现更高效的数据传输。

---

## **注意事项**

- 使用 HTTPS 请求时，需配置证书或禁用证书验证（仅限调试）。
- 长效访问令牌（Token）需妥善保管，避免泄露。

---

**示例代码已开源，欢迎贡献改进！**
