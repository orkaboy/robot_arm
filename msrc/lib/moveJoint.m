function [] = moveJoint(portNum,deviceID,startPos,endPos,startTime,endTime)
    time = toc;
    if(time > startTime && time < endTime)
    	wantedPos = startPos + smoothTraj((time-startTime)/(endTime-startTime))*(endPos-startPos);
        goalPos(portNum,deviceID,wantedPos);
    end
end

