#ifndef MQTT_SENDER_H
#define MQTT_SENDER_H

#include <Arduino.h>

// 初始化 MQTT 发送模块
void initMQTTSender();

// 发送温度数据到 MQTT
void sendMQTTTemperature(float temperature);

// 发送湿度数据到 MQTT
void sendMQTTHumidity(float humidity);

#endif
