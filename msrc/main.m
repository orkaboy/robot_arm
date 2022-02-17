clc; clear;
libName = setupLib();
portNum = setupPort('COM7');
setupMotors(portNum);
tic

%goToHome(portNum);
pause(1);
tic
while(toc < 3)
    moveJoint(portNum,2,512,700,0,1.5);
    moveJoint(portNum,2,700,400,1.5,3);
    moveJoint(portNum,3,512,700,1,2);
    moveJoint(portNum,0,512,300,0,1);
    moveJoint(portNum,0,300,600,1,2);
    moveJoint(portNum,1,512,650,0,2);
%     moveJoint(portNum,1,512,412,2,3);
%     moveJoint(portNum,2,512,412,2,3);
%     moveJoint(portNum,3,512,750,2,3);
%     moveJoint(portNum,0,512,800,0,2.6);
end
goToHome(portNum);
tic
while(toc < 6)

    moveJoint(portNum,1,512,412,2,3);
    moveJoint(portNum,2,512,412,2,3);
    moveJoint(portNum,3,512,750,2,3);
    moveJoint(portNum,0,512,800,0,2.6);
    moveJoint(portNum,1,412,500,4,6);
end

goToHome(portNum);

% Close port
closePort(portNum);

% Unload Library
unloadlibrary(libName);