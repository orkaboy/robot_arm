function [] = goalPos(portNum, deviceID, pos)
%UNTITLED4 Summary of this function goes here
%   Detailed explanation goes here
limits = [150,750;200,700;250,900;0,1023;0,1023;0,1023];

if(pos > limits(deviceID+1,2))
    pos = limits(deviceID+1,2);
elseif(pos < limits(deviceID+1,1))
    pos = limits(deviceID+1,1);
end
    write2ByteTxOnly(portNum, 1.0, deviceID, 30, pos);
end