#include "i2cgpio.h"
#include "Arduino.h"
#include "Wire.h"

uint8_t currentOutputValue = 0;

void initI2c() {
  pinMode(I2C_SDA_PIN, INPUT_PULLUP);
  pinMode(I2C_SCL_PIN, INPUT_PULLUP);
  Wire.setSDA(I2C_SDA_PIN);
  Wire.setSCL(I2C_SCL_PIN);
  Wire.begin();
}

void i2cWriteByte(uint8_t value){
Wire.beginTransmission(I2C_GPIO_PERIPHERAL_ADDRESS);
  Wire.write(value); 
  Wire.endTransmission();
}

uint8_t i2cReadByte(){
  uint8_t latestInputValue;
  Wire.requestFrom(I2C_GPIO_PERIPHERAL_ADDRESS, 1);
  while (Wire.available()) {
    latestInputValue=Wire.read();
  }
  return latestInputValue;
}

//set a given output pin in the gpio expander to the specified value
// with the current hardware, valid pinIndex values are 0 or 1
void setI2cGpioPin(uint8_t pinIndex, uint8_t value) {
  if (value) {
    currentOutputValue |= (1 << pinIndex); //set bit
  } else {
    currentOutputValue &= ~(1 << pinIndex); //clear bit
  }
  i2cWriteByte(currentOutputValue);
}

//set ALL output pins in the gpio expander to the specified value
// with the current hardware, valid values are 0x00 through 0x03
void setI2cGpioPins(uint8_t values) {
  currentOutputValue = values;
  i2cWriteByte(currentOutputValue);
}

//get the value of a given input pin in the gpio expander (returns 0 or 1)
// with the current hardware, valid pinIndex values are through 3
int getI2cGpioPin(uint8_t pinIndex) {
  return (i2cReadByte() >> pinIndex) & 1;
}

//get the value of ALL input pins in the GPIO expander, packed into low bits of the return value
// with current hardware, expected range us 0x00 through 0x0F
int getI2cGpioPins() {
  return i2cReadByte();
}
