cmake_minimum_required(VERSION 3.5)

project(jdbc-mysql-demo LANGUAGES CXX VERSION 1.0)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(mysqlcppconn_shared_path /usr/local/lib)

aux_source_directory(${PROJECT_SOURCE_DIR}/ src)

add_executable(jdbc-mysql-demo ${src})

find_library(mysqlcppconn_shared_libs NAMES mysqlcppconn ${mysqlcppconn_shared_path})

target_link_libraries(jdbc-mysql-demo PRIVATE
    ${mysqlcppconn_shared_libs}
)