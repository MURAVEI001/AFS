#include <Arduino.h>

void setup() {
  Serial.begin(115200);
}
void loop() {
  int wilg = analogRead(A0);
  int wil = map(wilg,310,570, 100, 0);
  Serial.println(wil);
  delay(500); 
}