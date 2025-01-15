#ifndef OTA_UPDATE_H
#define OTA_UPDATE_H

#include <ArduinoOTA.h>

// 初始化 OTA 更新功能
void setupOTA();

// 在主循环中处理 OTA 更新
void handleOTA();

#endif // OTA_UPDATE_H
