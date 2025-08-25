from machine import I2C, Pin, PWM
import time
import random
from Sengo2 import *

# Initialize I2C (adjust the pins according to the actual wiring
i2c = I2C(0, scl=Pin(21), sda=Pin(20), freq=400000)  # Use the pins in the reference code

# Wait for the initialization of Sengo2 (important!)
time.sleep(3)

# Create a Sengo2 object
sentry = Sengo2()

# Start sensor
if sentry.begin(i2c) != SENTRY_OK:
    print("Sentry initialization failed!")
    while True: pass

# Set the color block detection parameters - only detect red and blue
sentry.SetParamNum(sengo2_vision_e.kVisionBlob, 1)  # Set 1 group of parameter

# Red parameter group
sentry.SetParam(
    sengo2_vision_e.kVisionBlob,
    [0, 0, 5, 5, color_label_e.kColorRed],  # Parameter format
    param_id=1
)

# Enable the color block detection function
if sentry.VisionBegin(sengo2_vision_e.kVisionBlob) == SENTRY_OK:
    print("Color block detection enabled")
    

# right wheel
pin1=Pin(14,Pin.OUT)
pin2=PWM(Pin(16))
pin2.freq(50)

# left wheel
pin3=Pin(15,Pin.OUT)
pin4=PWM(Pin(17))
pin4.freq(50)

# As a function of the car going forward.
def car_forward(): 
  pin1.value(0)
  pin2.duty_u16(20000) 
  pin3.value(0)
  pin4.duty_u16(20000)

# As a function of the car going backwards.
def car_back(): 
  pin1.value(1)
  pin2.duty_u16(30000)  
  pin3.value(1)
  pin4.duty_u16(30000)

# As a function of the car going left.
def car_left(): 
  pin1.value(0)
  pin2.duty_u16(5000)  
  pin3.value(1)
  pin4.duty_u16(45000)
# As a function of the car going right.
def car_right(): 
  pin1.value(1)
  pin2.duty_u16(45000)  
  pin3.value(0)
  pin4.duty_u16(5000)

# As a function of the car stopping.
def car_stop(): 
  pin1.value(0)
  pin2.duty_u16(0)  
  pin3.value(0)
  pin4.duty_u16(0)
    

# loop
try:
    while True:
        # Obtain the number of detected color blocks
        obj_num = sentry.GetValue(sengo2_vision_e.kVisionBlob,sentry_obj_info_e.kStatus)
        
        if obj_num:
            # Obtain the coordinates and size
            x = sentry.GetValue(sengo2_vision_e.kVisionBlob,sentry_obj_info_e.kXValue,1)
            y = sentry.GetValue(sengo2_vision_e.kVisionBlob,sentry_obj_info_e.kYValue,1)
            w = sentry.GetValue(sengo2_vision_e.kVisionBlob,sentry_obj_info_e.kWidthValue,1)
            h = sentry.GetValue(sengo2_vision_e.kVisionBlob,sentry_obj_info_e.kHeightValue,1)
            if y >= 80:
                # the car moves backward
                car_back()
            elif x <= 20:
                # the car turns left
                car_left()
            elif x >= 80:
                # the car turns right
                car_right()
            elif w <= 15 and h <= 15:
                # the car moves forward
                car_forward()
            elif w >= 70 and h >= 70:
                # the car moves backward
                car_back()
            else:
                car_stop()
        else: car_stop()
        time.sleep(0.1)  # a short delay

except KeyboardInterrupt:
    sentry.VisionEnd(sengo2_vision_e.kVisionBlob)
    print("The program has stopped")
