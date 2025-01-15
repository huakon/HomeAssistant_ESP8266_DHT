#ifndef CONFIG_H
#define CONFIG_H

// WiFi 配置
const char* WIFI_SSID = "你的WiFi名称";
const char* WIFI_PASSWORD = "你的WiFi密码";

// Home Assistant 配置
const char* hass_url_temp = "https://your_home_assistant_url/api/states/sensor.dht_temperature";
const char* hass_url_humidity = "https://your_home_assistant_url/api/states/sensor.dht_humidity";
const char* hass_token = "YOUR_HASS_TOKEN";

// 是否启用 HTTPS 验证（true 为验证证书，false 为跳过验证）
const bool skipCertificateVerification = false;

#endif // CONFIG_H