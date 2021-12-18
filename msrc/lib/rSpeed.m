function currSpeed = rSpeed(portNum,deviceID)
%UNTITLED8 Summary of this function goes here
%   Detailed explanation goes here

currSpeed = read2ByteTxRx(portNum,1.0,deviceID, 38);
end