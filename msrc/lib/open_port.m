function port_num = open_port(devicename, baudrate)

port_num = portHandler(devicename);
packetHandler();
dxl_comm_result = COMM_TX_FAIL;

if (openPort(port_num))
    fprintf('Succeeded to open the port!\n');
else
    unloadlibrary(lib_name);
    fprintf('Failed to open the port!\n');
    input('Press any key to terminate...\n');
    return;
end

if (setBaudRate(port_num, baudrate))
    fprintf('Succeeded to change the baudrate!\n');
else
    unloadlibrary(lib_name);
    fprintf('Failed to change the baudrate!\n');
    input('Press any key to terminate...\n');
    return;
end

end