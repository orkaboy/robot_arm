function [] = LED(port_num, deviceID, mode)
%port num is the open port given by the function open_port
%deviceID is which motor to write to
%mode is either ON or OFF

if (strcmp(mode, 'ON'))
    write1ByteTxRx(port_num, PROTOCOL_VERSION, deviceID, ADDR_LED, 1);
elseif (strcmp(mode, 'OFF'))
    write1ByteTxRx(port_num, PROTOCOL_VERSION, deviceID, ADDR_LED, 0);
end
 
end