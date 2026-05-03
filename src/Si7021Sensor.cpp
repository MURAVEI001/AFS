#include <Arduino.h>
#include <Wire.h>

#define SENSOR_ADDR 0x40

float readHTU21D_Humidity() {
  Wire.begin();
  Wire.beginTransmission(SENSOR_ADDR);
  Wire.write(0xE5);  // КОМАНДА HTU21D для влажности
  Wire.endTransmission();
  
  delay(50);  // HTU21D нужно больше времени (50мс для 12-bit)
  
  Wire.requestFrom(SENSOR_ADDR, 3);  // HTU21D возвращает 3 байта!
  if (Wire.available() < 3) return -999;
  
  uint16_t raw = Wire.read() << 8;
  raw |= Wire.read();
  Wire.read();  // Читаем контрольную сумму (игнорируем)
  
  raw &= 0xFFFC;  // Сбрасываем статусные биты
  
  float humidity = -6.0 + 125.0 * raw / 65536.0;
  if (humidity > 100) humidity = 100;
  if (humidity < 0) humidity = 0;
  
  return humidity;
}

float readHTU21D_Temperature() {
  Wire.begin();
  Wire.beginTransmission(SENSOR_ADDR);
  Wire.write(0xE3);  // КОМАНДА HTU21D для температуры
  Wire.endTransmission();
  
  delay(50);
  
  Wire.requestFrom(SENSOR_ADDR, 3);
  if (Wire.available() < 3) return -999;
  
  uint16_t raw = Wire.read() << 8;
  raw |= Wire.read();
  Wire.read();
  
  raw &= 0xFFFC;
  
  float temperature = -46.85 + 175.72 * raw / 65536.0;
  
  return temperature;
}