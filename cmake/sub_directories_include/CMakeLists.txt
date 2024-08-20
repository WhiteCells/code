cmake_minimum_required(VERSION 3.5)

project(app LANGUAGES CXX VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(${PROJECT_SOURCE_DIR}/global)

include(${PROJECT_SOURCE_DIR}/session/session.cmake)
message(STATUS "session source: " ${session_src})

add_subdirectory(${PROJECT_SOURCE_DIR}/server)
# message(STATUS "server source: " ${server_src})

# set(src ${PROJECT_SOURCE_DIR}/main.cpp ${session_src} ${server_src})
set(src ${PROJECT_SOURCE_DIR}/main.cpp ${session_src})

add_executable(${PROJECT_NAME} ${src})

target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/global)
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/session)
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/server)

target_link_libraries(${PROJECT_NAME} PRIVATE global_lib server_lib)