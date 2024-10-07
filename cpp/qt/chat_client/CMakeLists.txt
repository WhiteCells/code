cmake_minimum_required(VERSION 3.5)

project(chat-client LANGUAGES CXX VERSION 1.0)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Widgets)

aux_source_directory(${PROJECT_SOURCE_DIR}/src/ src)
aux_source_directory(${PROJECT_SOURCE_DIR}/src/widget widget_src)

set(qrc_src
    ${PROJECT_SOURCE_DIR}/resources/icon/icon.qrc
    ${PROJECT_SOURCE_DIR}/resources/qss/qss.qrc
)

qt_add_executable(${PROJECT_NAME} 
    ${src}
    ${chat_stacked_widget_src}
    ${list_stacked_widget_src}
    ${widget_src}
    ${qrc_src}
)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets)

target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/src)