cmake_minimum_required(VERSION 3.5)

project(circular VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB PROJECT_SOURCES
    ${PROJECT_SOURCE_DIR}/element/*.cpp
    ${PROJECT_SOURCE_DIR}/visitor/*.cpp
    ${PROJECT_SOURCE_DIR}/*.cpp
)

add_executable(circular ${PROJECT_SOURCES})

include_directories(
    ${PROJECT_SOURCE_DIR}/visitor
    ${PROJECT_SOURCE_DIR}/element
)