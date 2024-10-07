cmake_minimum_required(VERSION 3.10)

project(func_lib LANGUAGES CXX VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

set(func_src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/func.cpp
)

# add_library(${PROJECT_NAME} SHARED ${func_src})
# add_library(${PROJECT_NAME} STATIC ${func_src})
add_library(func_lib STATIC ${func_src})

# 指定库的头文件
# target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(func_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

message(STATUS ${PROJECT_SOURCE_DIR})