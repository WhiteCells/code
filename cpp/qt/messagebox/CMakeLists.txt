cmake_minimum_required(VERSION 3.5)

project(messagebox-example LANGUAGES CXX VERSION 1.0)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

aux_source_directory(${PROJECT_SOURCE_DIR}/ src)

include_directories(${PROJECT_SOURCE_DIR})

qt_add_executable(demo
    ${src}
)

target_link_libraries(demo PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
)