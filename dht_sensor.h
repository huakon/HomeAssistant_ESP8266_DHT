#ifndef DHT_SENSOR_H
#define DHT_SENSOR_H

#include <Arduino.h>

// 初始化 DHT 传感器
void initDHT();

// 读取温度数据
float readTemperature();

// 读取湿度数据
float readHumidity();

#endif
