cmake_minimum_required(VERSION 3.5)

project(button-demo LANGUAGES CXX VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(QT NAMES Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Widgets)

aux_source_directory(${PROJECT_SOURCE_DIR} src)

qt_add_executable(${PROJECT_NAME} ${src})

target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets)

target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR})