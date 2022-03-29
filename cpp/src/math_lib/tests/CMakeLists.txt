
add_executable(vec-tests vec-tests.cpp)
target_link_libraries(vec-tests ARC::math)

add_executable(mat-tests mat-tests.cpp)
target_link_libraries(mat-tests ARC::math)

add_executable(quat-tests quat-tests.cpp)
target_link_libraries(quat-tests ARC::math)

add_executable(bezier-tests bezier-tests.cpp)
target_link_libraries(bezier-tests ARC::math)

add_test(Vec3Construct vec-tests 0)

add_test(Mat3Construct mat-tests 0)

add_test(QuatConstruct quat-tests 0)

add_test(BezierConstruct bezier-tests 0)
