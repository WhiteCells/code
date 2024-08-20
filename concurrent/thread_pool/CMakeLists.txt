cmake_minimum_required(VERSION 3.5)

project(thread_pool LANGUAGES CXX VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SRC
    ./*.cpp
    ./*.tpp
)

add_executable(thread_pool ${SRC})