#include "robot_lib.hpp"
#include "debug.hpp"

#include <fmt/core.h>
#include <unistd.h>

#include <thread>
#include <chrono>
#include <filesystem>

auto main(int argc, char* argv[]) -> int {
    std::string config_file = "config/config.yml";
    ARC::Real speed_limit = 0.1;

	int c;
	while ((c = getopt(argc, argv, "c:s:")) != -1) {
		switch(c) {
		case 'c': {
			config_file = optarg;
			fmt::print("Setting config file path: '{}'\n", config_file);
			break;
		}
        case 's': {
            speed_limit = std::stof(optarg);
            fmt::print("Setting speed multiplier to {}.\n", speed_limit);
            break;
        }
		default:
			fmt::print("Unsupported commandline argument: '{}'\n", c);
			return -1;
		}
	}

    if(!std::filesystem::exists(config_file)) {
        fmt::print("Missing config file '{}'\n", config_file);
        return -1;
    }

    ARC::RobotArm arm(config_file);
    if(!arm.IsOK()) {
        fmt::print("Unable to initialize robot arm.\n");
        if(!ARC::DEBUG()) {
            return -1;
        }
    }


    arm.Enable(true);
    // TEMP TODO Set positions
    // Just for safety, limit speeds
    fmt::print("Limiting speed to {}%...\n", speed_limit * 100);
    arm.SetSpeed(speed_limit);

    fmt::print("Moving to origin...\n");
    std::vector<ARC::Real> origin = {0,0,0,0,0,0};
    arm.SetJoints(origin);
    
    using namespace std::chrono_literals;

    if(!ARC::DEBUG()) {
        while(!arm.JointsIsDoneMoving(origin)) {
            std::this_thread::sleep_for(10ms);
        }
    }

    std::this_thread::sleep_for(2s);

    fmt::print("Moving to high...\n");
    std::vector<ARC::Real> top = {0,0,1,0,0,0};
    arm.SetJoints(top);
    if(!ARC::DEBUG()) {
        while(!arm.JointsIsDoneMoving(top)) {
            std::this_thread::sleep_for(10ms);
        }
    }

    std::this_thread::sleep_for(2s);

    using namespace std::chrono_literals;
    arm.MoveToPos(ARC::vec3(0.1, 0.1, 0.1), 1s);
    
    std::this_thread::sleep_for(2s);

    fmt::print("Done! Shutting down...\n");

    return 0;
}
