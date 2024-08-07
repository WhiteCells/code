cmake_minimum_required(VERSION 3.5)

project(visitor VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(${PROJECT_BINARY_DIR})
set(${PROJECT_VERSION})

file(GLOB PROJECT_SOURCES
    ./object/*.cpp
    ./visitor/*.cpp
    ./*.cpp
)

add_executable(visitor ${PROJECT_SOURCES})

include_directories(
    ./object
    ./visitor
)