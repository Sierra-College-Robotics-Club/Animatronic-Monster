#ifndef USRF_H
#define USRF_H

#include <Arduino.h>

#ifdef __cplusplus
extern "C" {
#endif

#define TRIG_PIN_1 4
#define ECHO_PIN_1 5
#define TRIG_PIN_2 3
#define ECHO_PIN_2 2

void initUSRF(void);
int getDistance(uint8_t sensor);

#ifdef __cplusplus
}
#endif

#endif