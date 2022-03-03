function [robotAngles] = qmapping(qAngles)
%QMAPPING Maps q angles in radians to robot angles
map = [1023, 1023, 1023, 1023, 1023, 1023]/5.2360;
orientation = [-1,-1,-1,-1,-1,-1];
angleShift = [0, pi/2, -pi/2, -pi/2, -pi/2, 0];

    for i = 1:6
        robotAngles(i) = round(map(i)*(qAngles(i).JointPosition * orientation(i) + angleShift(i)+ 2.6180))
    end
end

