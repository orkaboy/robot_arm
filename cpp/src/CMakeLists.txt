add_subdirectory(math_lib)
add_subdirectory(robot_lib)

find_package(Threads REQUIRED)

add_executable(robot_arm main.cpp)
target_link_libraries(robot_arm ARC::robot Threads::Threads)

add_executable(limit_calc limit_calc.cpp)
target_link_libraries(limit_calc fmt::fmt)

if(SIM)
    add_executable(sim sim.cpp)
    target_link_libraries(sim PUBLIC igl::glfw ARC::robot)
endif(SIM)
