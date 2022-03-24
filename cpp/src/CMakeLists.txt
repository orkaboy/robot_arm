
add_subdirectory(robot_lib)

add_executable(ping ping.cpp)
target_link_libraries(ping VENDOR::dxl)
