# C++ implementation of Robot Arm project

Using the AX-12A servos from Dynamixel, mounted in the robot arm designed by ARC Sweden. This is an attempt to run the control code on a more embedded platform (using the odroid), in order to reduce latencies in the system. The code intends to model the robot arm and create a library interface for it, using the C++ backend of Dynamixel SDK.

# Prerequisites

* Build and install the Dynamixel SDK c++ library (DynamixelSDK/c++/build/linux64, run make, sudo make install)
    - May require to remove the `FORMAT=-m64` line on the odroid in order to compile
* Install CMake

# Building

```
mkdir build
cd build
cmake ..
make -j
```

# Running

* Connect robot USB to the odroid and power the robot
* Verify that device appears as `/dev/ttyUSB0`
* Ensure servos are configured according to the `config.yml` file

Run, with elevated scheduler priority:

```
chrt -r 1 ./robot-arm
```
