# Robot Arm

## Installation

Run the python setup file to install the library:

	cd DynamixelSDK/python/
	sudo python setup.py install

## Usage

### with wrapper

By importing the Ax12 class from the Ax12.py file you can use all the methods.
Look in the example.py file.
	
	# import the class
	from Ax12 import Ax12

	# specify the usb port
	Ax12.DEVICENAME = '/dev/ttyUSB0'

	# specify baudrate
	Ax12.BAUDRATE = 1\_000\_000

	# sets baudrate and opens com port
	Ax12.connect()

	# create AX12 instance with ID 1 
	motor_id = 1
	my_dxl = Ax12(motor_id)  
	my_dxl.set_moving_speed(200)

	# move the servo
	my_dxl.set_goal_position(90)

	# disconnect
	my_dxl.set_torque_enable(0)
	Ax12.disconnect()

### without wrapper

Look at test2.py. Make sure to use 1000000 baud rate. Make sure to use the right control table adresses for the AX-12A dynamixel.
