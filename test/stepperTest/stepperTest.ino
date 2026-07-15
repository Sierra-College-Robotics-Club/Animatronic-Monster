#include "stepper.h"

void setup() {
  Serial.begin(115200);
  initStepper();
  Serial.println("Stepper ready");
}

void loop() {
  setSpeedUs(10000);
  moveStepsDir(100, LOW);
  delay(500);

  moveStepsDir(100, HIGH);
  delay(500);
}