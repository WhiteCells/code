cmake_minimum_required(VERSION 3.5)

project(factor_method VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB PROJECT_SOURCES
    ${PROJECT_SOURCE_DIR}/factory/*.cpp
    ${PROJECT_SOURCE_DIR}/product/*.cpp
    ${PROJECT_SOURCE_DIR}/*.cpp
)

add_executable(factor_method ${PROJECT_SOURCES})

include_directories(
    ${PROJECT_SOURCE_DIR}/factory
    ${PROJECT_SOURCE_DIR}/product
)