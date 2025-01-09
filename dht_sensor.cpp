#include "dht_sensor.h"
#include <DHT.h>

// DHT 配置
#define DHTPIN D2
#define DHTTYPE DHT11

// 初始化 DHT 对象
DHT dht(DHTPIN, DHTTYPE);

void initDHT() {
  dht.begin();
}

float readTemperature() {
  return dht.readTemperature();
}

float readHumidity() {
  return dht.readHumidity();
}
