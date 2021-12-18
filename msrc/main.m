clc; clear;
libName = setupLib();
portNum = setupPort('COM7');
setupMotors(portNum);
tic

goToHome(portNum);

% Close port
closePort(portNum);

% Unload Library
unloadlibrary(libName);