function [] = led(portNum, deviceID, mode)
%port num is the open port given by the function open_port
%deviceID is which motor to write to
%mode is either ON or OFF

if (strcmp(mode, 'ON'))
    write1ByteTxOnly(portNum, 1.0, deviceID, 25, 1);
elseif (strcmp(mode, 'OFF'))
    write1ByteTxOnly(portNum, 1.0, deviceID, 25, 0);
end
 
end