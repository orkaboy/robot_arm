
# DXL SDK
add_library(dxl_lib INTERFACE)
target_link_libraries(dxl_lib INTERFACE dxl_x64_cpp)
add_library(VENDOR::dxl ALIAS dxl_lib)

