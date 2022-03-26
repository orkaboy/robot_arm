
add_library(robot_lib
    robot_lib.cpp
    debug.cpp
    motor.cpp
    ax-12a.cpp
)
target_link_libraries(robot_lib
    VENDOR::dxl
    fmt::fmt
    ryml::ryml
)
target_include_directories(robot_lib PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)
add_library(ARC::robot ALIAS robot_lib)
