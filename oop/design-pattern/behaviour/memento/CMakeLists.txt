cmake_minimum_required(VERSION 3.5)

project(memento VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB PROJECT_SOURCES
    ${PROJECT_SOURCE_DIR}/caretaker/*.cpp
    ${PROJECT_SOURCE_DIR}/memento/*.cpp
    ${PROJECT_SOURCE_DIR}/originator/*.cpp
    ${PROJECT_SOURCE_DIR}/*.cpp
)

add_executable(memento ${PROJECT_SOURCES})

include_directories(
    ${PROJECT_SOURCE_DIR}/caretaker
    ${PROJECT_SOURCE_DIR}/memento
    ${PROJECT_SOURCE_DIR}/originator
)