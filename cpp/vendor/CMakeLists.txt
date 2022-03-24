
# DXL SDK
add_library(dxl_lib INTERFACE)
target_link_libraries(dxl_lib INTERFACE dxl_x64_cpp)
add_library(VENDOR::dxl ALIAS dxl_lib)

# FMT lib
include(FetchContent)
FetchContent_Declare(fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt.git
  GIT_TAG 8.1.1
)
FetchContent_MakeAvailable(fmt)
