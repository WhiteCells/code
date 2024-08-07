cmake_minimum_required(VERSION 3.5)

project(redis-demo LANGUAGES CXX VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

aux_source_directory(${PROJECT_SOURCE_DIR} src)

find_library(hiredis_lib NAMES hiredis PATH /usr/local/lib)

add_executable(redis-demo ${src})

target_link_libraries(redis-demo PRIVATE
    ${hiredis_lib}
)