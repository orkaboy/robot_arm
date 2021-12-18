function [] = movingSpeed(portNum,deviceID,speed)
%UNTITLED7 Summary of this function goes here
%   Detailed explanation goes here
if(speed > 1023)
    speed = 1023;
elseif(speed < 0)
    speed = 0;
end
    write2ByteTxOnly(portNum, 1.0, deviceID, 34, speed);
end
