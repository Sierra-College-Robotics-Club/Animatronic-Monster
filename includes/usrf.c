#include "usrf.h"

const unsigned long TIMEOUT_USRF_US = 30000UL;

static const uint8_t trigPins[2] = { TRIG_PIN_1, TRIG_PIN_2 };
static const uint8_t echoPins[2] = { ECHO_PIN_1, ECHO_PIN_2 };

void initUSRF(void) {
  pinMode(TRIG_PIN_1, OUTPUT);
  pinMode(ECHO_PIN_1, INPUT);
  pinMode(TRIG_PIN_2, OUTPUT);
  pinMode(ECHO_PIN_2, INPUT);

  digitalWrite(TRIG_PIN_1, LOW);
  digitalWrite(TRIG_PIN_2, LOW);
}

int getDistance(uint8_t sensor) {
  if (sensor > 1) return -1;

  uint8_t trigPin = trigPins[sensor];
  uint8_t echoPin = echoPins[sensor];

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  unsigned long duration = pulseIn(echoPin, HIGH, TIMEOUT_USRF_US);

  if (duration == 0) {
    return -1;
  }

  return (int)(duration * 0.0343 / 2.0);
}