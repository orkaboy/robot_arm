
add_library(testbench INTERFACE)
target_include_directories(testbench INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)
add_library(ARC::tb ALIAS testbench)
