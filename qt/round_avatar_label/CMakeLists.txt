cmake_minimum_required(VERSION 3.5)

project(round_avatar_label_demo LANGUAGES CXX VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(QT NAMES Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

aux_source_directory(${PROJECT_SOURCE_DIR}/ src)

set(qrc_src
    ${PROJECT_SOURCE_DIR}/resources/icon/icon.qrc
)

qt_add_executable(${PROJECT_NAME} 
    ${src}
    ${qrc_src})

target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)