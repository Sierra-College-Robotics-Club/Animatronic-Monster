#include "usrf.h"

void setup() {
  Serial.begin(115200);
  initUSRF();
}

void loop() {
  int d1 = getDistance(0);
  delay(50);
  int d2 = getDistance(1);

  Serial.print("Sensor 0: ");
  Serial.print(d1);
  Serial.print(" cm\tSensor 1: ");
  Serial.print(d2);
  Serial.println(" cm");

  delay(100);
}