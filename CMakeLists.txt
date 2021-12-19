cmake_minimum_required(VERSION 3.10)
project(ThreadC LANGUAGES CXX)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})
add_executable(main src/main.cpp src/demothread.cpp)
find_package (Threads)
target_link_libraries (main ${CMAKE_THREAD_LIBS_INIT})
