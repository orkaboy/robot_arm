function [] = setup_motors(port_num)
    for deviceID = 0:5
        torque_enable(port_num,deviceID,'ON');
        torque_limit(port_num,deviceID,1023);
        write2ByteTxRx(port_num, 1.0, deviceID, 32, 1023);
    end
end

