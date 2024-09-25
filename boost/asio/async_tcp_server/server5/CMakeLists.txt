cmake_minimum_required(VERSION 3.5)

project(server LANGUAGES CXX VERSION 1.0)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

aux_source_directory(${PROJECT_SOURCE_DIR}/ server_src)

add_executable(${PROJECT_NAME} ${server_src})