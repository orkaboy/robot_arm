
add_library(fabrik fabrik.cpp)
target_include_directories(fabrik PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)
target_link_libraries(fabrik ARC::math)
add_library(ARC::IK ALIAS fabrik)
