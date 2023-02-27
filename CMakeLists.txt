cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

project(soil VERSION 0.0.1)

set(src_files
    src/version.cpp
)

add_library(${PROJECT_NAME} SHARED ${src_files})

configure_file(include/config.h.in config.h)
include_directories(BEFORE 
    ${PROJECT_BINARY_DIR}
    include
    third_party
)

add_executable(test_version test/test_version.cpp)
target_link_libraries(test_version ${PROJECT_NAME})
