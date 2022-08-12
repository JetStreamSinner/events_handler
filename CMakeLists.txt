cmake_minimum_required(VERSION 3.18)
project(EventsHandler)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()
add_subdirectory(source)
set(CMAKE_CXX_FLAGS -pthread)

if(${BUILD_SAMPLES})
    add_subdirectory(examples)
endif()