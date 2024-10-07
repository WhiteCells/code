cmake_minimum_required(VERSION 3.5)

project(observer VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB PROJECT_SOURCES
    ${PROJECT_SOURCE_DIR}/*.cpp
)

add_executable(observer ${PROJECT_SOURCES})

include_directories(
    ${PROJECT_SOURCE_DIR}/observer
    ${PROJECT_SOURCE_DIR}/subject
)