
add_subdirectory(robot_lib)

add_executable(robot_arm main.cpp)
target_link_libraries(robot_arm ARC::robot)

