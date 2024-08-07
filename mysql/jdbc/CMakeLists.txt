cmake_minimum_required(VERSION 3.5)

project(jdbc-mysql-demo LANGUAGES CXX VERSION 1.0)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(mysqlcppconn_shared_path /usr/local/lib)
set(src
    mysql_connect_pool.cpp
    example.cpp
)

add_executable(jdbc-mysql-demo ${src})

find_library(mysqlcppconn_shared_libs NAMES mysqlcppconn ${mysqlcppconn_shared_path})
message(STATUS "Found mysqlcppconn so: ${mysqlcppconn_sharedlibs}")

target_link_libraries(jdbc-mysql-demo PRIVATE
    ${mysqlcppconn_shared_libs}
)