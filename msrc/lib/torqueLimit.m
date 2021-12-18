function [] = torqueLimit(portNum, deviceID, torqueLim)
%UNTITLED4 Summary of this function goes here
%   Detailed explanation goes here
if(torqueLim > 1023)
    torqueLim = 1023;
elseif(torqueLim < 0)
    torqueLim = 0;
end
    write2ByteTxOnly(portNum, 1.0, deviceID, 34, torqueLim);
end