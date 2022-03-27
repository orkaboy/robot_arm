
add_library(math_lib vector.cpp)
target_include_directories(math_lib PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)
add_library(ARC::math ALIAS math_lib)

