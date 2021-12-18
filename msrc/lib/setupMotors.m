function [] = setupMotors(portNum)
    for deviceID = 0:5
        torqueEnable(portNum, deviceID,'ON');
        torqueLimit(portNum, deviceID,1023);
        movingSpeed(portNum, deviceID, 1023);
    end
end

