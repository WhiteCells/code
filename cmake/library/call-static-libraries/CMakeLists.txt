cmake_minimum_required(VERSION 3.20.0)

project(call-static-libraries LANGUAGES CXX)

include_directories(${PROJECT_SOURCE_DIR}/include)

link_directories(${PROJECT_SOURCE_DIR}/lib)

add_executable(app main.cpp)

target_link_libraries(app PUBLIC test2)