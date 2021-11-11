from Ax12 import Ax12

class Robot():
    motors = []

    def __init__(self, devicename, baudrate, default_speed, *args):
        Ax12.DEVICENAME = devicename
        Ax12.BAUDRATE = baudrate
        Ax12.connect()

        for idx, id in enumerate(args):
            self.motors.append(Ax12(id))
            self.motors[idx].enable_torque()
            self.motors[idx].set_moving_speed(default_speed)


if __name__ == "__main__":
    robot_arm = Robot('/dev/ttyUSB0', 1_000_000, 200, 1)
    while True:
        print("Position of dxl ID: %d is %d " %
              (robot_arm.motors[0].id, robot_arm.motors[0].get_present_position()))
        # desired angle input
        input_pos = int(input("goal pos: "))
        robot_arm.motors[0].set_goal_position(input_pos)
        while abs(input_pos - robot_arm.motors[0].get_present_position()) > 2:
            print("Position of dxl ID: %d is %d " %
                  (robot_arm.motors[0].id, robot_arm.motors[0].get_present_position()))

