cmake_minimum_required(VERSION 3.5)

project(proxy VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB PROJECT_SOURCES
    ${PROJECT_SOURCE_DIR}/proxy/*.cpp
    ${PROJECT_SOURCE_DIR}/service/*.cpp
    ${PROJECT_SOURCE_DIR}/*.cpp
)

add_executable(proxy ${PROJECT_SOURCES})

include_directories(
    ${PROJECT_SOURCE_DIR}/proxy
    ${PROJECT_SOURCE_DIR}/service
)