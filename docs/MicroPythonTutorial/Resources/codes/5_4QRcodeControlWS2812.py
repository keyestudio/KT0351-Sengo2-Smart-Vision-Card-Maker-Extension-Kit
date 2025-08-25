from machine import I2C,UART,Pin
from  Sengo2  import *
import time
from neopixel import myNeopixel

# Wait for Sengo2 to complete the initialization of the operating system. This waiting time cannot be removed to prevent the situation where the controller has already developed and sent instructions before Sengo2 has been fully initialized
time.sleep(3)

# Choose UART or I2C communication mode. Sengo2 is I2C mode by default. You can switch between the two by short pressing the mode button.
# Four UART communication modes: UART9600 (Standard Protocol Instruction), UART57600 (Standard Protocol Instruction), UART115200 (Standard Protocol Instruction), Simple9600 (Simple Protocol Instruction)
#########################################################################################################
# port = UART(2,rx=Pin(16),tx=Pin(17),baudrate=9600)
port = I2C(0,scl=Pin(21),sda=Pin(20),freq=400000)

# The communication address of Sengo2 is 0x60. If multiple devices are connected to the I2C bus, please avoid address conflicts.
sengo2 = Sengo2(0x60)

err = sengo2.begin(port)
print("sengo2.begin: 0x%x"% err)

 
# 1 Sengo2 can only recognize and decode a QR code with no more than 10 characters.
# 2. Pay attention that QR code is not Apriltag. When in use, we should remain a blank space around them.
# 3. During normal use, the main controller sends commands to control the on and off of Sengo2 algorithm, rather than manual operation by joystick.
# 4. Sengo2 can run multiple algorithms simultaneously, but there are certain restrictions.
err = sengo2.VisionBegin(sengo2_vision_e.kVisionQrCode)
print("sengo2.VisionBegin(sengo2_vision_e.kVisionQrCode):0x%x"% err)

#Define the number of pin and LEDs connected to neopixel.
NUM_LEDS = 4
np = myNeopixel(NUM_LEDS, 13)
np.brightness(150) #brightness: 0 ~ 255

lastDetectionTime = 0

while True:
# Sengo2 does not actively return the detection and recognition results; it requires the main control board to send instructions for reading.
# The reading process: 1.read the number of recognition results. 2.After receiving the instruction, Sengo2 will refresh the result data. 3.If the number of results is not zero, the board will then send instructions to read the relevant information. 
# (Please be sure to build the program according to this process.)
    obj_num = sengo2.GetValue(sengo2_vision_e.kVisionQrCode, sentry_obj_info_e.kStatus)
    # Sengo2 can only recognize and decode a QR code with no more than 10 characters. So when the returned result is not 0, it is only necessary to obtain and process the relevant data of the first result.
    # Obtain the running time
    currentMillis = time.ticks_ms()
    if obj_num:
        lastDetectionTime = currentMillis
        QRcodeStr = sengo2.GetQrCodeValue()
        if QRcodeStr == "Red":
            np.fill(255,0,0)
            np.show()
        elif QRcodeStr == "Green":
            np.fill(0,255,0)
            np.show()
        elif QRcodeStr == "Blue":
            np.fill(0,0,255)
            np.show()
        elif QRcodeStr == "Black":
            np.fill(0,0,0)
            np.show()
        elif QRcodeStr == "White":
            np.fill(255,255,255)
            np.show()
    # If the QR code is not detected within 5 seconds, turn off the WS2812
    if currentMillis - lastDetectionTime >= 5000:
        lastDetectionTime = currentMillis
        np.fill(0,0,0)
        np.show()
