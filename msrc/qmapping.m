function [robotAngles] = qmapping(qAngles)
%QMAPPING Maps q angles in radians to robot angles
orientation = [-1,-1,-1,-1,-1,-1];
angleShift = [0, pi/2-0.1357, -pi/2-0.1357, -pi/2, -pi/2, 0];

    for i = 1:6
        robotAngles(i) = floor(orientation(i)*(qAngles(i).JointPosition+angleShift(i))/2.6180*511.5 + 511.5);
    end
end

