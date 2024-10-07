cmake_minimum_required(VERSION 3.5)

project(command VERSION 0.1 LANGUAGES CXX)

file(GLOB PROJECT_SOURCES
    ${PROJECT_SOURCE_DIR}/command/*.cpp
    ${PROJECT_SOURCE_DIR}/control/*.cpp
    ${PROJECT_SOURCE_DIR}/*.cpp
)

add_executable(command ${PROJECT_SOURCES})

include_directories(
    ${PROJECT_SOURCE_DIR}/command
    ${PROJECT_SOURCE_DIR}/control
)
