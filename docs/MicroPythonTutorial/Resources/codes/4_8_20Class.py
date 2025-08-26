from machine import I2C,UART,Pin
from Sengo2 import *
import time

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
 
# 1: Sengo2 can run multiple algorithms simultaneously, but there are certain restrictions.
# 2. The parameter and result numbers of the sengo/sentry series products all start from 1.
# 3. During normal use, the main controller sends commands to control the on and off of Sengo2 algorithm, rather than manual operation by joystick.
err = sengo2.VisionBegin(sengo2_vision_e.kVision20Classes)
print("sengo2.VisionBegin(sengo2_vision_e.kVision20Classes):0x%x"% err)

#20classes object names
classes20Name = ["unknown",			"Airplane", 		"Bicycle",  	"Bird",			"Boat",
                 "Bottle",			"Bus",				"Car",			"Cat",			"Chair",
                 "Cow",				"Dining Table",		"Dog",			"Horse",    	"Motorbike",
                 "Person",			"Potted Plant",		"Sheep",		"Sofa",			"Train",
                 "TV Monitor"]

while True:
# Sengo2 does not actively return the detection and recognition results; it requires the main control board to send instructions for reading.
# The reading process: 1.read the number of recognition results. 2.After receiving the instruction, Sengo2 will refresh the result data. 3.If the number of results is not zero, the board will then send instructions to read the relevant information. 
# (Please be sure to build the program according to this process.)
    obj_num = (sengo2.GetValue(sengo2_vision_e.kVision20Classes, sentry_obj_info_e.kStatus))
    if obj_num:
        print("Totally %d objects: "%( obj_num ))
        for i in range(1,obj_num+1):
            l = sengo2.GetValue(sengo2_vision_e.kVision20Classes,sentry_obj_info_e.kLabel,i)
            x = sengo2.GetValue(sengo2_vision_e.kVision20Classes, sentry_obj_info_e.kXValue, i)
            y = sengo2.GetValue(sengo2_vision_e.kVision20Classes, sentry_obj_info_e.kYValue, i)
            w = sengo2.GetValue(sengo2_vision_e.kVision20Classes, sentry_obj_info_e.kWidthValue, i)
            h = sengo2.GetValue(sengo2_vision_e.kVision20Classes, sentry_obj_info_e.kHeightValue, i)
            print("obj%d: x=%d, y=%d, w=%d, h=%d, label=%s"%(i,x, y, w, h,classes20Name[l]))
            time.sleep(0.2)
            print("\n")
        time.sleep(0.5);
       