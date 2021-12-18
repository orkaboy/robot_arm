clc; clear;
lib_name = setup_lib();
port_num = open_port('COM7');
setup_motors(port_num);



% Close port
closePort(port_num);

% Unload Library
unloadlibrary(lib_name);