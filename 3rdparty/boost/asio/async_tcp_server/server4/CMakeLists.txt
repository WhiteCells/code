cmake_minimum_required(VERSION 3.5)

project(server)

set(CMAKE_CXX_STANDARD 11)

aux_source_directory(${PROJECT_SOURCE_DIR}/ src)

add_executable(${PROJECT_NAME} ${src})