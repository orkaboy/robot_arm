# TODO Robot arm testing

* Set up odroid system (Ubuntu 16.04 xenial, aarch64)
* login: odroid odroid
* Downloaded robot_arm repo and submodule DynamixelSDK
* Connected servos (need USB->odroid and power)
* Servos are AX-12A: https://emanual.robotis.com/docs/en/dxl/ax/ax-12a/
    * Servos support protocol version 1.0
    * Baudrate is set to 1000000
    * Servos have programmed IDs
    * Can use DYNAMIXEL Wizard program to scan/read/write
* Can build c++ stack, using linux64 Makefile:
    * Need to remove FORMAT=-m64 flag from Makefile
    * Build and make install
    * Need to change the DXL_ID, BAUD_RATE in the example programs (use Protocol 1.0)
* In order to run the servos in read_write example, need to set the CW/CCW limits
    * Goal/CW/CCW are in range 0..1023
    * Set Torque mode
    * Can also run free-running, set speed (can rotate freely, but the positional encoders don't work)


## TODO next

* Set up CW/CCW degrees conversion
* Model robot arm limits (IDs 0-5)
* Test running entire robot arm between limits (limit speed!)
* Model IK (FABRIK?)
* What timing can be achieved?
    * Test with `chrt -r 1` and us timers
* What applications can be made?
    * Move point-to-point
    * Control with gamepad