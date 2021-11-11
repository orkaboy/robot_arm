from Ax12 import Ax12
from time import sleep

# e.g 'COM3' windows or '/dev/ttyUSB0' for Linux
Ax12.DEVICENAME = '/dev/ttyUSB0'

Ax12.BAUDRATE = 1_000_000

# sets baudrate and opens com port
Ax12.connect()

# create AX12 instance with ID 10 
my_dxl = Ax12(1)  
my_dxl.set_moving_speed(100)
my_dxl.set_id(my_dxl.id)

sleep(1)

my_dxl2 = Ax12(2)  
my_dxl2.set_moving_speed(100)
my_dxl2.set_id(my_dxl2.id)

def user_input():
    """Check to see if user wants to continue"""
    ans = input('Continue? : y/n ')
    if ans == 'n':
        return False
    else:
        return True


def main(motor_object):
    """ sets goal position based on user input """
    bool_test = True
    while bool_test:
        for motor in motor_object:
            print("Position of dxl ID: %d is %d " % (motor.id, motor.get_present_position()))
        input_pos = int(input("goal pos: "))
        for motor in motor_object:
            motor.set_goal_position(input_pos)

        bool_test = user_input()

# pass in AX12 object
main([my_dxl, my_dxl2])

# disconnect
my_dxl.set_torque_enable(0)
Ax12.disconnect()
