cmake_minimum_required(VERSION 3.11)

project(test)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SRC
    acc.cc
    call.cc
    main.cc
)

add_executable(${PROJECT_NAME} ${SRC})
