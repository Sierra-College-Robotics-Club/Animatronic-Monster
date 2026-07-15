#include "stepper.h"
#include "usrf.h"
#include "i2cgpio.h"
#include <Servo.h>

Servo jawServo;
int servoPos = 0;    // variable to store the servo position

typedef enum {STOP, RUN} runMode;
runMode mode;

void setup() {
  Serial.begin(115200);
  Serial.println("starting gancho-lookaround");
  initStepper();
  setSpeedUs(10000);
  initUSRF();
  initI2c();
  jawServo.attach(6); //use LED OUT 1 Port for JawServo
  Serial.println("setup complete");
}


void loop() {
  if(getI2cGpioPin(0) == 0){
    mode = STOP;
  }
  if(getI2cGpioPin(1) == 0){
    mode = RUN;
  }
  if (mode == RUN){
    for (servoPos = 155; servoPos >= 0; servoPos -= 1) { // goes from 180 degrees to 0 degrees
      jawServo.write(servoPos);              // tell servo to go to position in variable 'pos'
      moveStepsDir(1, LOW);
      //delay(10);                       // waits 15 ms for the servo to reach the position
    }
    for (servoPos = 0; servoPos <= 155; servoPos += 1) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      jawServo.write(servoPos);              // tell servo to go to position in variable 'pos'
      moveStepsDir(1, HIGH);
      //delay(10);                       // waits 15 ms for the servo to reach the position
    }
  }
}