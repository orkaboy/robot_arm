% Add SDK folder plus all subfolders to the path.
addpath(genpath("../DynamixelSDK"));
addpath(genpath("lib"));
clc;
clear all;
load("addresses.mat");
lib_name = '';
%Determine cpu architecture
if strcmp(computer, 'PCWIN')
  lib_name = 'dxl_x86_c';
elseif strcmp(computer, 'PCWIN64')
  lib_name = 'dxl_x64_c';
elseif strcmp(computer, 'GLNX86')
  lib_name = 'libdxl_x86_c';
elseif strcmp(computer, 'GLNXA64')
  lib_name = 'libdxl_x64_c';
elseif strcmp(computer, 'MACI64')
  lib_name = 'libdxl_mac_c';
end
% Load Libraries
if ~libisloaded(lib_name)
    [notfound, warnings] = loadlibrary(lib_name, 'dynamixel_sdk.h', 'addheader', 'port_handler.h', 'addheader', 'packet_handler.h');
end

% Protocol version
PROTOCOL_VERSION                = 1.0;          % See which protocol version is used in the Dynamixel

% Default setting
DXL_ID                          = 2;            % Dynamixel ID: 1
BAUDRATE                        = 1000000;
DEVICENAME                      = 'COM7';       % Check which port is being used on your controller
COMM_SUCCESS                    = 0;            % Communication Success result value
COMM_TX_FAIL                    = -1001;        % Communication Tx Failed                                                % ex) Windows: 'COM1'   Linux: '/dev/ttyUSB0' Mac: '/dev/tty.usbserial-*'

ADDR_LED                        = 25;
ADDR_POS                        = 36;

% Initialize PortHandler Structs
% Set the port path
% Get methods and members of PortHandlerLinux or PortHandlerWindows
port_num = portHandler(DEVICENAME);

% Initialize PacketHandler Structs
packetHandler();

dxl_comm_result = COMM_TX_FAIL;                 % Communication result

% Open port
if (openPort(port_num))
    fprintf('Succeeded to open the port!\n');
else
    unloadlibrary(lib_name);
    fprintf('Failed to open the port!\n');
    input('Press any key to terminate...\n');
    return;
end

% Set port baudrate
if (setBaudRate(port_num, BAUDRATE))
    fprintf('Succeeded to change the baudrate!\n');
else
    unloadlibrary(lib_name);
    fprintf('Failed to change the baudrate!\n');
    input('Press any key to terminate...\n');
    return;
end

write2ByteTxRx(port_num, PROTOCOL_VERSION, 2, 36, 1023);
write2ByteTxRx(port_num, PROTOCOL_VERSION, 1, 36, 1023);
write2ByteTxRx(port_num, PROTOCOL_VERSION, 0, 36, 1023);
write2ByteTxRx(port_num, PROTOCOL_VERSION, 2, 32, 1023);
write2ByteTxRx(port_num, PROTOCOL_VERSION, 1, 32, 1023);
write2ByteTxRx(port_num, PROTOCOL_VERSION, 0, 32, 1023);

runTime = 5;
startPos = 800;
endPos = 500;
startPos2 = 512;
endPos2 = 400;
startPos3 = 700;
endPos3 = 800;
tic
while toc < runTime %while not at goal
    currTime = toc;
    wantedPos = startPos + smoothTraj(currTime/runTime)*(endPos-startPos);
    wantedPos2 = startPos2 + smoothTraj(currTime/runTime)*(endPos2-startPos2);
    wantedPos3 = startPos3 + smoothTraj(currTime/runTime)*(endPos3-startPos3);
    goal_pos(port_num,2,wantedPos);
    goal_pos(port_num,1,wantedPos2);
    goal_pos(port_num,0,wantedPos3);
end
startPos = 500;
endPos = 800;
startPos2 = 400;
endPos2 = 512;
startPos3 = 800;
endPos3 = 700;
tic
while toc < runTime %while not at goal
    currTime = toc;
    %wantedPos = startPos+currTime*((endPos-startPos)/runTime);
    wantedPos = startPos + smoothTraj(currTime/runTime)*(endPos-startPos);
    wantedPos2 = startPos2 + smoothTraj(currTime/runTime)*(endPos2-startPos2);
    wantedPos3 = startPos3 + smoothTraj(currTime/runTime)*(endPos3-startPos3);
    goal_pos(port_num,2,wantedPos);
    goal_pos(port_num,1,wantedPos2);
    goal_pos(port_num,0,wantedPos3);
end


%%FELix
% for i = 1:3
% write1ByteTxRx(port_num, PROTOCOL_VERSION, DXL_ID, ADDR_LED, 1);
% dxl_comm_result = getLastTxRxResult(port_num, PROTOCOL_VERSION);
% dxl_error = getLastRxPacketError(port_num, PROTOCOL_VERSION);
% if dxl_comm_result ~= COMM_SUCCESS
%     fprintf('%s\n', getTxRxResult(PROTOCOL_VERSION, dxl_comm_result));
% elseif dxl_error ~= 0
%     fprintf('%s\n', getRxPacketError(PROTOCOL_VERSION, dxl_error));
% end
% pause(1)
% write1ByteTxRx(port_num, PROTOCOL_VERSION, DXL_ID, ADDR_LED, 0);
% dxl_comm_result = getLastTxRxResult(port_num, PROTOCOL_VERSION);
% dxl_error = getLastRxPacketError(port_num, PROTOCOL_VERSION);
% if dxl_comm_result ~= COMM_SUCCESS
%     fprintf('%s\n', getTxRxResult(PROTOCOL_VERSION, dxl_comm_result));
% elseif dxl_error ~= 0
%     fprintf('%s\n', getRxPacketError(PROTOCOL_VERSION, dxl_error));
% end
% pause(1)
% end

% Close port
closePort(port_num);

% Unload Library
unloadlibrary(lib_name);
disp("Done");
close all;
clear all;