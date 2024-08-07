cmake_minimum_required(VERSION 3.5)

project(mysql-demo LANGUAGES CXX VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

aux_source_directory(${PROJECT_SOURCE_DIR}/ src)

add_executable(mysql-demo ${src})

target_link_libraries(mysql-demo PRIVATE mysqlclient)
