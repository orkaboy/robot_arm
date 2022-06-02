
add_executable(fabrik-tests fabrik-tests.cpp)
target_link_libraries(fabrik-tests ARC::IK ARC::tb)

add_test(FABRIKLinkConstruct fabrik-tests 0)
add_test(FABRIKConstruct fabrik-tests 1)
add_test(FABRIKConstraints fabrik-tests 2)
add_test(FABRIKForwardKinematics fabrik-tests 3)
