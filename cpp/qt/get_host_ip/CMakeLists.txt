cmake_minimum_required(VERSION 3.5)

project(demo LANGUAGES CXX VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(QT NAMES Qt6 REQUIRED COMPONENTS Widgets Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Network)

set(src
    # ${PROJECT_SOURCE_DIR}/get_host_ip.cpp
    ${PROJECT_SOURCE_DIR}/get_rand_port.cpp
)

qt_add_executable(${PROJECT_NAME} 
    ${src})

target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt6::Network)