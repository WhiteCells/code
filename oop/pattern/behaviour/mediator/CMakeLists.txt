cmake_minimum_required(VERSION 3.5)

project(mediator VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB PROJECT_SOURCES
    ${PROJECT_SOURCE_DIR}/mediator/*.cpp
    ${PROJECT_SOURCE_DIR}/user/*.cpp
    ${PROJECT_SOURCE_DIR}/*.cpp
)

add_executable(mediator ${PROJECT_SOURCES})

include_directories(
    ${PROJECT_SOURCE_DIR}/mediator
    ${PROJECT_SOURCE_DIR}/user
)