cmake_minimum_required(VERSION 3.5)

project(builder VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB PROJECT_SOURCES
    ${PROJECT_SOURCE_DIR}/builder/*.cpp
    ${PROJECT_SOURCE_DIR}/director/*.cpp
    ${PROJECT_SOURCE_DIR}/product/*.cpp
    ${PROJECT_SOURCE_DIR}/*.cpp
)

add_executable(builder ${PROJECT_SOURCES})

include_directories(
    ${PROJECT_SOURCE_DIR}/builder
    ${PROJECT_SOURCE_DIR}/director
    ${PROJECT_SOURCE_DIR}/product
)
