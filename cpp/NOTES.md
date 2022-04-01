# Robot arm testing

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

## C++ port

* Set up CW/CCW degrees conversion
* Set up move-to-origin test app
* Set up config.yml file
* Set up a dry-run debug mode
* Set up math library with vec3, mat3 and quat
* Set up simple FABRIK implementation of IK (unconstrained)
* Implemented curve function (Bezier)

## TODO next

* Implement hinge joints as part of FABRIK
* Implement full IK (with joint constraints and target orientation)
* Implement link pos <-> angle functions for IK
* Model robot arm limits (lengths for IDs 0-5, joint limits)
* Test running entire robot arm (limit speed!)
* What timing can be achieved?
    * Test with `chrt -r 1` and us timers
* What applications can be made?
    * Move point-to-point (smooth move by interpolating with IK)
    * Control with gamepad
