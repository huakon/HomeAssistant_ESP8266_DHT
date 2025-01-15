#ifndef CONFIG_H
#define CONFIG_H

// WiFi 配置
const char* WIFI_SSID = "你的WiFi名称";
const char* WIFI_PASSWORD = "你的WiFi密码";

// Home Assistant 配置
const char* HASS_URL = "https://hass.hamsterking.xyz/api/states";
const char* HASS_TOKEN = "你的长令牌";

// 是否启用 HTTPS 验证（true 为验证证书，false 为跳过验证）
const bool ENABLE_HTTPS = false;

#endif // CONFIG_H