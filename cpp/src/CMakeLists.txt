
add_subdirectory(robot_lib)

add_executable(ping ping.cpp)
target_link_libraries(ping VENDOR::dxl)

add_executable(robot_arm main.cpp)
target_link_libraries(robot_arm ARC::robot)

