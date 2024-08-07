cmake_minimum_required(VERSION 3.5)

project(prototype VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB PROJECT_SOURCES
    ${PROJECT_SOURCE_DIR}/*.cpp
)

add_executable(prototype ${PROJECT_SOURCES})

include_directories(
    ${PROJECT_SOURCE_DIR}/concrete
    ${PROJECT_SOURCE_DIR}/prototype
)