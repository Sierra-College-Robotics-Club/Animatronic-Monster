#include "stepper.h"
#include "usrf.h"
#include "i2cgpio.h"

void setup() {
  Serial.begin(115200);
  Serial.println("starting gancho-lookaround");
  initStepper();
  initUSRF();
  initI2c();
  Serial.println("setup complete");
}

void loop() {
  // put your main code here, to run repeatedly:
}