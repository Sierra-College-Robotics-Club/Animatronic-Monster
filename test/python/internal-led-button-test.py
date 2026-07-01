from machine import Pin #,PWM,ADC
from time import sleep


led1 = Pin(25,  Pin.OUT)
btn1 = Pin(14, Pin.IN, Pin.PULL_DOWN)

led1.on
while(True):
    if(btn1.value() == 1):
        led1.on()
    else:
        led1.off()
