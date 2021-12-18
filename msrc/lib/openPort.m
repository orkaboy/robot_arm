function portNum = openPort(deviceName)
baudrate = 1000000;
portNum = portHandler(deviceName);
packetHandler();

if (openPort(portNum))
    disp('Succeeded to open the port!\n');
else
    disp('Failed to open the port!\n');
    return;
end

if (setBaudRate(portNum, baudrate))
    disp('Succeeded to change the baudrate!\n');
else
    disp('Failed to change the baudrate!\n');
    return;
end

end