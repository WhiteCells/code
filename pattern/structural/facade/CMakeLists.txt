cmake_minimum_required(VERSION 3.5)

project(facade VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB PROJECT_SOURCES
    ${PROJECT_SOURCE_DIR}/*.cpp
    ${PROJECT_SOURCE_DIR}/facade/*.cpp
    ${PROJECT_SOURCE_DIR}/system/*.cpp
)

add_executable(facade ${PROJECT_SOURCES})

include_directories(
    ${PROJECT_SOURCE_DIR}/facade
    ${PROJECT_SOURCE_DIR}/system
)