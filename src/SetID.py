from Ax12 import Ax12
COMM_SUCCESS = 0  # tx or rx packet communication success


if __name__ == "__main__":
    Ax12.DEVICENAME = '/dev/ttyUSB0' 
    Ax12.BAUDRATE = 1_000_000
    Ax12.connect()

    num_motors = int(input("Input number of motors: "))
    for i in range(num_motors):
        input("Plug in motor %s, press any key when done." % (i+1))
        iter_id = 0
        while True:
            motor = Ax12(iter_id)
            res, comm_result, dxl_err = motor.get_id()
            if comm_result == COMM_SUCCESS and dxl_err == 0:
                found_motor = True
                id = iter_id
                print("Motor found at id %s" % (id))
                break
            if iter_id > 1024:
                print("Motor not found")
                exit()
            iter_id = iter_id + 1
        new_id = int(input("Give motor %s id: " % (i+1)))
        motor.set_id(new_id)
        print("Motor now has id %s." % (motor.get_id()[0]))

