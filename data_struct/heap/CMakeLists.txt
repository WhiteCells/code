cmake_minimum_required(VERSION 3.5)

project(heap_example LANGUAGES CXX VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SRC
    ${PROJECT_SOURCE_DIR}/example.cpp
)

add_executable(heap_example ${SRC})