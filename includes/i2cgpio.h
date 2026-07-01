#ifndef I2CGPIO_H
#define I2CGPIO_H

#include "Arduino.h"

#ifdef __cplusplus
extern "C" {
#endif

#define I2C_GPIO_PERIPHERAL_ADDRESS 37 /* 0x25 */
#define I2C_SDA_PIN 20
#define I2C_SCL_PIN 21

void initI2c();
void setI2cGpioPin(uint8_t pinIndex, uint8_t value);
void setI2cGpioPins(uint8_t values);
int getI2cGpioPin(uint8_t pinIndex);
int getI2cGpioPins();

#ifdef __cplusplus
}
#endif

#endif