function [] = goToHome(portNum)
    home = [512 525 530 520 512 512];
    for i = 0:5
        pause(0.1);
    	startPos(i+1) = read2ByteTxRx(portNum, 1.0, i, 36);
    end
    sT = toc;
    while toc < sT + 7
       moveJoint(portNum,0,startPos(1),home(1),sT +0,sT +7);
       moveJoint(portNum,1,startPos(2),home(2),sT +1,sT +3);
       moveJoint(portNum,2,startPos(3),home(3),sT +2,sT +4);
       moveJoint(portNum,3,startPos(4),home(4),sT +3,sT +5);
       moveJoint(portNum,4,startPos(5),home(5),sT +4,sT +6);
       moveJoint(portNum,5,startPos(6),home(6),sT +5,sT +7);
    end
end

