from machine import I2C,Pin  #I2C Start 
sclPin = Pin(21, Pin.OUT)
sdaPin  = Pin(20, Pin.OUT)
i2c = I2C(freq=400000,sda = sdaPin, scl= sclPin )           # create I2C peripheral at frequency of 400kHz
                                # depending on the port, extra parameters may be required
                                # to select the peripheral and/or pins to use

print (i2c.scan())                      # scan for peripherals, returning a list of 7-bit addresses
print (bytes([3]))
while(1):
    #i2c.writeto(37, bytes([3]))         # write 3 bytes to peripheral with 7-bit address 42
    button_values = i2c.readfrom(37, 1)             # read 4 bytes from peripheral with 7-bit address 42
                           #I2C Finish
    if (button_values[0] & 1) == 0:
       print ("First Button Pressed") 
    if (button_values[0] & 2) == 0: 
        print  ("Second Button Pressed")
    if (button_values[0] & 4) == 0:
        print  ("Third Button Pressed")
        
