clc; 
libName = setupLib();
portNum = setupPort('COM3');
setupMotors(portNum);
tic

goToHome(portNum);
pause(1);
tic
t = toc;
while t < trajTime
    
    i = floor(t*fps)+1;
    currPos = qmapping(q(i,:));
    for m = 0:5
        goalPos(portNum, m, currPos(m+1));
    end
    t = toc;
end

goToHome(portNum);

% Close port
closePort(portNum);

% Unload Library
unloadlibrary(libName);