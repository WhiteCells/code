cmake_minimum_required(VERSION 3.5)

project(dproject LANGUAGES CXX VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(dproject1 main1.cpp)
add_executable(dproject2 main2.cpp)