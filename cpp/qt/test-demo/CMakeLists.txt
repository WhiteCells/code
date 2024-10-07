cmake_minimum_required(VERSION 3.10)
project(test-demo LANGUAGES CXX VERSION 1.0)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# find_package(QT NAMES Qt6 REQUIRED COMPONENTS Widgets WebEngineCore WebEngineWidgets)
# find_package(Qt6 REQUIRED COMPONENTS Widgets WebEngineCore WebEngineWidgets)

find_package(Qt6 REQUIRED COMPONENTS Widgets WebEngineCore WebEngineWidgets)

set(src
    ${PROJECT_SOURCE_DIR}/main.cpp
    ${PROJECT_SOURCE_DIR}/widget.cpp
)

add_executable(${PROJECT_NAME} ${src})

target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets Qt6::WebEngineCore Qt6::WebEngineWidgets)
