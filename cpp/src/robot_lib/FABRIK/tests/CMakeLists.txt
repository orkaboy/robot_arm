
add_executable(fabrik-tests fabrik-tests.cpp)
target_link_libraries(fabrik-tests ARC::IK ARC::tb)

add_test(FABRIKLinkConstruct fabrik-tests 0)

