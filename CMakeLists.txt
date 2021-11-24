cmake_minimum_required(VERSION 3.16)
project(MultiThreading)

set(CMAKE_CXX_STANDARD 20)
add_compile_options(-I./)
add_executable(MultiThreading main.cpp)

target_link_libraries(MultiThreading pthread)
