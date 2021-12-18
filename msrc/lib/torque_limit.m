function [] = torque_limit(port_num, deviceID, torque_lim)
%UNTITLED4 Summary of this function goes here
%   Detailed explanation goes here
if(torque_lim > 1023)
    torque_lim = 1023;
elseif(torque_lim < 0)
    torque_lim = 0;
end
    write2ByteTxRx(port_num, 1.0, deviceID, 34, torque_lim);
end