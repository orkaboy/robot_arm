function currPos = rPos(portNum,deviceID)
%UNTITLED8 Summary of this function goes here
%   Detailed explanation goes here

currPos = read2ByteTxRx(portNum,1.0,deviceID, 36);
end