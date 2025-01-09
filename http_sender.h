#ifndef HTTP_SENDER_H
#define HTTP_SENDER_H

#include <Arduino.h>

// 初始化 HTTP 发送模块
void initHTTPSender();

// 通过 HTTP PUT 发送温度数据
void sendHTTPTemperature(float temperature);

// 通过 HTTP PUT 发送湿度数据
void sendHTTPHumidity(float humidity);

#endif
