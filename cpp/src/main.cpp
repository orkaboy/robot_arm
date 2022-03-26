#include "robot_lib.hpp"

#include <fmt/core.h>
#include <unistd.h>

#include <thread>
#include <chrono>

auto main(int argc, char* argv[]) -> int {
    std::string config_file = "config/config.yml";

	int c;
	while ((c = getopt(argc, argv, "c:")) != -1) {
		switch(c) {
		case 'c': {
			config_file = optarg;
			fmt::print("Setting config file path: '{}'\n", config_file);
			break;
		}
		default:
			fmt::print("Unsupported commandline argument: {}\n", c);
			return -1;
		}
	}

    ARC::RobotArm arm(config_file);
    if(!arm.IsOK()) {
        fmt::print("Unable to initialize robot arm.\n");
        //return -1;
    }

    // TEMP TODO Set positions
    fmt::print("Moving to origin...\n");
    std::vector<float> origin = {0,0,0,0,0,0};
    arm.SetJoints(origin);
    while(!arm.JointsIsDoneMoving(origin)) {
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(10ms);
        break; //TODO
    }
    fmt::print("Done! Shutting down...\n");

    return 0;
}
