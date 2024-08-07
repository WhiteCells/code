cmake_minimum_required(VERSION 3.5)

project(double-free-demo LANGUAGES CXX VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_library(hiredis_lib NAMES hiredis PATH /usr/local/lib)

set(src
    double_free.cpp
)

add_executable(double-free-demo ${src})

target_link_libraries(double-free-demo PRIVATE 
    ${hiredis_lib}
)