cmake_minimum_required(VERSION 3.5)

project(adapter VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB PROJECT_SOURCES
    ${PROJECT_SOURCE_DIR}/*.cpp
    ${PROJECT_SOURCE_DIR}/hole/*.cpp
    ${PROJECT_SOURCE_DIR}/round/*.cpp
    ${PROJECT_SOURCE_DIR}/round_adapter/*.cpp
    ${PROJECT_SOURCE_DIR}/square/*.cpp
)

add_executable(adapter
    ${PROJECT_SOURCES}
)

include_directories(
    ${PROJECT_SOURCE_DIR}/hole
    ${PROJECT_SOURCE_DIR}/round
    ${PROJECT_SOURCE_DIR}/round_adapter
    ${PROJECT_SOURCE_DIR}/square
)