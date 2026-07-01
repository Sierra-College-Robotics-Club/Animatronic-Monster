#include "stepper.h"

static int stepDelayUs = 10000;
static bool stepDirection = LOW;

void initStepper(void) {
  pinMode(STEP_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);
  digitalWrite(STEP_PIN, LOW);
  digitalWrite(DIR_PIN, stepDirection);
}

void setDirection(bool dir) {
  stepDirection = dir;
  digitalWrite(DIR_PIN, stepDirection);
}

void setSpeedUs(int delayUs) {
  stepDelayUs = delayUs;
}

void stepPulse(void) {
  digitalWrite(STEP_PIN, HIGH);
  delayMicroseconds(stepDelayUs);
  digitalWrite(STEP_PIN, LOW);
  delayMicroseconds(stepDelayUs);
}

void moveSteps(long steps) {
  for (long i = 0; i < steps; i++) {
    stepPulse();
  }
}

void moveStepsDir(long steps, bool dir) {
  setDirection(dir);
  moveSteps(steps);
}