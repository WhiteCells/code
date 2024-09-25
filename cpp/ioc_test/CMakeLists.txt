cmake_minimum_required(VERSION 3.5)

project(ioc_test LANGUAGES CXX VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

aux_source_directory(${PROJECT_SOURCE_DIR}/ src)

add_executable(${PROJECT_NAME} ${src})