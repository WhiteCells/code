cmake_minimum_required(VERSION 3.5)

project(user_list_widget_demo LANGUAGES CXX VERSION 1.0)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Widgets)

aux_source_directory(${PROJECT_SOURCE_DIR} src)

qt_add_executable(${PROJECT_NAME} ${src})

target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets)