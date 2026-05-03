#include <Arduino.h>
#define SENSOR_PIN A0

int readSoilHumidity() {
  int rawValue = analogRead(SENSOR_PIN);
  
  // ВСТАВЬТЕ СВОИ ЧИСЛА:
  int dryValue = 520;   // RAW на сухом воздухе
  int wetValue = 260;   // RAW в воде
  
  int moisturePercent;
  
  if (rawValue >= dryValue) {
    moisturePercent = 0;
  } else if (rawValue <= wetValue) {
    moisturePercent = 100;
  } else {
    moisturePercent = map(rawValue, dryValue, wetValue, 0, 100);
  }
  
  return moisturePercent;
}