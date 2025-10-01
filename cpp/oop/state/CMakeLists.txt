cmake_minimum_required(VERSION 3.10)

project(state LANGUAGES CXX VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SRC
    main.cc
)

add_executable(${PROJECT_NAME} ${SRC})
