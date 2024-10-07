cmake_minimum_required(VERSION 3.5)

project(chain_of_responsibility VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED NO)

file(GLOB PROJECT_SOURCES
    ${PROJECT_SOURCE_DIR}/handler/*.cpp
    ${PROJECT_SOURCE_DIR}/order/*.cpp
    ${PROJECT_SOURCE_DIR}/*.cpp
)

add_executable(chain_of_responsibility ${PROJECT_SOURCES})

include_directories(
    ${PROJECT_SOURCE_DIR}/handler
    ${PROJECT_SOURCE_DIR}/order
)