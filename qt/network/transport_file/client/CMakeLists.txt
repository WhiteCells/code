cmake_minimum_required(VERSION 3.5)

project(client LANGUAGES CXX VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(QT NAMES Qt6 REQUIRED COMPONENTS Widgets Network)
find_package(Qt6 REQUIRED COMPONENTS Widgets Network)

aux_source_directory(${PROJECT_SOURCE_DIR} src)

qt_add_executable(${PROJECT_NAME} ${src})

target_link_libraries(client PRIVATE Qt6::Widgets Qt6::Network)