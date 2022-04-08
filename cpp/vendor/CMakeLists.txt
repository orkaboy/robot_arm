include(FetchContent)

# DXL SDK
add_library(dxl_lib INTERFACE)
target_link_libraries(dxl_lib INTERFACE dxl_x64_cpp)
add_library(VENDOR::dxl ALIAS dxl_lib)

# FMT lib
FetchContent_Declare(fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt.git
  GIT_TAG 8.1.1
)
FetchContent_MakeAvailable(fmt)

# RapidYAML
if(RYML_BRANCH_NAME STREQUAL "")
    find_program(GIT git REQUIRED)
    execute_process(COMMAND git rev-parse --abbrev-ref HEAD
        OUTPUT_VARIABLE RYML_BRANCH_NAME
        OUTPUT_STRIP_TRAILING_WHITESPACE)
endif()
if(RYML_BRANCH_NAME STREQUAL HEAD)
    set(RYML_BRANCH_NAME master)
endif()
message(STATUS "FetchContent from branch: ${RYML_BRANCH_NAME}")

FetchContent_Declare(ryml
    GIT_REPOSITORY https://github.com/biojppm/rapidyaml.git
    GIT_TAG ${RYML_BRANCH_NAME}
    GIT_SHALLOW FALSE  # ensure submodules are checked out
)
FetchContent_MakeAvailable(ryml)

if(SIM)
    # libigl
    FetchContent_Declare(
        libigl
        GIT_REPOSITORY https://github.com/libigl/libigl.git
        GIT_TAG v2.4.0
    )
    FetchContent_MakeAvailable(libigl)
endif(SIM)
