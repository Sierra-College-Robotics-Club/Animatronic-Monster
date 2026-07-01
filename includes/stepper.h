#ifndef STEPPER_H
#define STEPPER_H

#include <Arduino.h>

#ifdef __cplusplus
extern "C" {
#endif

#define STEP_PIN 19
#define DIR_PIN  18

void initStepper(void);
void setDirection(bool dir);
void setSpeedUs(int delayUs);
void stepPulse(void);
void moveSteps(long steps);
void moveStepsDir(long steps, bool dir);

#ifdef __cplusplus
}
#endif

#endif