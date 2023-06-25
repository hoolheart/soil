cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

project(soil VERSION 0.0.1)

file(GLOB src_files
    "src/*.cpp"
    "src/util/*.cpp"
    "src/signal/*.cpp"
    "src/geo/*.cpp"
)

add_library(${PROJECT_NAME} SHARED ${src_files})

include(GenerateExportHeader)
generate_export_header(${PROJECT_NAME})

configure_file(include/config.h.in config.h)
include_directories(BEFORE
    ${PROJECT_BINARY_DIR}
    include
    third_party
)

option(BUILD_TEST "Whether to build test executives" ON)

if(BUILD_TEST)
    file(GLOB tests "test/*.cpp")
    foreach(test_file ${tests})
        cmake_path(GET test_file STEM test_name)
        add_executable(${test_name} ${test_file})
        target_link_libraries(${test_name} ${PROJECT_NAME})
    endforeach()
endif()
