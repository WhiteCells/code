cmake_minimum_required(VERSION 3.5)

project(grpc-client VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Protobuf CONFIG REQUIRED)
find_package(gRPC CONFIG REQUIRED)

aux_source_directory(${PROJECT_SOURCE_DIR} grpc_client_src)
aux_source_directory(${PROJECT_SOURCE_DIR}/proto proto_src)

add_executable(${PROJECT_NAME} ${grpc_client_src} ${proto_src})

target_link_libraries(${PROJECT_NAME} PRIVATE gRPC::grpc++)

target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR})