const int stepPin = 19;
const int dirPin  = 18;

int stepDelayUs = 10000;   // controls speed
bool stepDirection  = LOW;    // LOW / HIGH

void initStepper() {
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  digitalWrite(stepPin, LOW);
  digitalWrite(dirPin, stepDirection);
}

void setDirection(bool dir) {
  stepDirection = dir;
  digitalWrite(dirPin, stepDirection);
}

void setSpeedUs(int delayUs) {
  stepDelayUs = delayUs;
}

void stepPulse() {
  digitalWrite(stepPin, HIGH);
  delayMicroseconds(stepDelayUs);
  digitalWrite(stepPin, LOW);
  delayMicroseconds(stepDelayUs);
}

void moveSteps(long steps) {
  for (long i = 0; i < steps; i++) {
    stepPulse();
  }
}

void moveSteps(long steps, bool dir) {
  setDirection(dir);
  moveSteps(steps);
}

void setup() {
  Serial.begin(115200);
  initStepper();
  Serial.println("Stepper ready");
}

void loop() {
  setSpeedUs(10000);
  setDirection(LOW);
  moveSteps(1000);
  delay(500);
  setDirection(HIGH);
  moveSteps(1000);
  delay(500);
}