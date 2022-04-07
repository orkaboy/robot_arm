cmake_minimum_required(VERSION 3.0)

set(CXX_STANDARD 17)

project(robot-arm VERSION 0.1)

enable_testing()

add_subdirectory(vendor)
add_subdirectory(src)
