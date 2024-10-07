cmake_minimum_required(VERSION 3.5)

project(flyweight VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQURED ON)

file(GLOB PROJECT_SOURCES
    ${PROJECT_SOURCE_DIR}/normal_pot/*.cpp
    ${PROJECT_SOURCE_DIR}/pot/*.cpp
    ${PROJECT_SOURCE_DIR}/pot_type/*.cpp
    ${PROJECT_SOURCE_DIR}/pot_type_factory/*.cpp
    ${PROJECT_SOURCE_DIR}/*.cpp
)

add_executable(flyweight ${PROJECT_SOURCES})

include_directories(
    ${PROJECT_SOURCE_DIR}/normal_pot
    ${PROJECT_SOURCE_DIR}/pot
    ${PROJECT_SOURCE_DIR}/pot_type
    ${PROJECT_SOURCE_DIR}/pot_type_factory
)