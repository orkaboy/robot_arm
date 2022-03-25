#include "robot_lib.hpp"

#include <fmt/core.h>
#include <unistd.h>

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
    if(!arm.Init()) {
        fmt::print("Unable to initialize robot arm.\n");
        return 1;
    }

    return 0;
}
