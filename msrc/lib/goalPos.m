function [] = goalPos(portNum, deviceID, pos)
%UNTITLED4 Summary of this function goes here
%   Detailed explanation goes here
if(pos > 1023)
    pos = 1023;
elseif(pos < 0)
    pos = 0;
end
    write2ByteTxOnly(portNum, 1.0, deviceID, 30, pos);
end