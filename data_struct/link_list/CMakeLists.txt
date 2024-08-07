cmake_minimum_required(VERSION 3.5)

project(link_list_demo LANGUAGES CXX VERSION 1.1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED 11)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})

set(SRC example.cpp)

add_executable(link_list_demo ${SRC})