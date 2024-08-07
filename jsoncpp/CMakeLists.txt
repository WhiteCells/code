cmake_minimum_required(VERSION 3.5)

project(jsonlib-demo LANGUAGES CXX VERSION 1.1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

configure_file(
    ${PROJECT_SOURCE_DIR}/server.json
    ${PROJECT_BINARY_DIR}/server.json
    COPYONLY
)

aux_source_directory(${PROJECT_SOURCE_DIR}/ src)

add_executable(jsonlib-demo ${src})

target_link_libraries(jsonlib-demo PRIVATE jsoncpp)