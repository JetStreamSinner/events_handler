set(src main.cpp scheduler.cpp event_loop.cpp event.cpp)
set(CMAKE_CXX_FLAGS -pthread)
add_executable(${PROJECT_NAME} ${src})
