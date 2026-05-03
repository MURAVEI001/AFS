#include <Arduino.h>
#include "OLED_I2C.h"

#include "Si7021Sensor.cpp"
#include "SoilSensor.cpp"

OLED myOLED(SDA, SCL, 8);

extern uint8_t TinyFont[];
extern uint8_t SmallFont[];
extern uint8_t MediumNumbers[];
extern uint8_t BigNumbers[];

float temperature; 
int humidity, soilHumidity;

void setup(){
   myOLED.begin();
   myOLED.setFont(BigNumbers);
}

void loop(){
    temperature = readHTU21D_Temperature();
    humidity = readHTU21D_Humidity();
    soilHumidity = readSoilHumidity();

    myOLED.printNumF(temperature, 1, 0, 0);
    myOLED.update();

    myOLED.printNumI(humidity, 0, 25);
    myOLED.update();

    myOLED.printNumI(soilHumidity, 40, 25);
    myOLED.update();

    delay(5000);

    if(soilHumidity == 100 or humidity == 100){
        myOLED.clrScr();
    }
}