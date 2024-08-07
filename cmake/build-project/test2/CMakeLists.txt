cmake_minimum_required(VERSION 3.20.0)
project(test2 CXX)
include(src/test.cmake)
add_executable(app main.cpp ${test_source})