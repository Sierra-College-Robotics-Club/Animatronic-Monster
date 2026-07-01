#include "i2cgpio.h"

#define LED_PIN 33

void setup()
{
  pinMode(LED_PIN, OUTPUT);
  initI2c();
  Serial.begin(115200);
  Serial.println("starting");
}

byte x = 0;

void loop()
{
  setI2cGpioPins(x);
  Serial.println("sent");
  delay(100);
  x = getI2cGpioPins();
  Serial.printf("value = %d\n",x);
  digitalWrite(LED_PIN, !digitalRead(LED_PIN));
  if (getI2cGpioPin(0)==0){
    Serial.println("Button 0");
  }
  if (getI2cGpioPin(1)==0){
    Serial.println("Button 1");
  }
  if (getI2cGpioPin(2)==0){
    Serial.println("Button 2");
  }
  //button 3 not installed on hardware, but supported by gpio driver ic
  if (getI2cGpioPin(3)==0){
    Serial.println("Button 3");
  }
  delay(100);
}
