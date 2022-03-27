add_subdirectory(math_lib)
add_subdirectory(robot_lib)

find_package(Threads REQUIRED)

add_executable(robot_arm main.cpp)
target_link_libraries(robot_arm ARC::robot Threads::Threads)

