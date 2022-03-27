
add_library(math_lib
    vec.cpp
    mat.cpp
    quat.cpp
    bezier.cpp
)
target_include_directories(math_lib PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)
target_link_libraries(math_lib fmt::fmt)
add_library(ARC::math ALIAS math_lib)
