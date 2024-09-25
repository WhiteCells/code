cmake_minimum_required(VERSION 3.5)

project(grpc-demo LANGUAGES CXX VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Protobuf CONFIG REQUIRED)
find_package(gRPC CONFIG REQUIRED)

aux_source_directory(${PROJECT_SOURCE_DIR}/grpc_client grpc_client_src)
aux_source_directory(${PROJECT_SOURCE_DIR}/grpc_server grpc_server_src)
aux_source_directory(${PROJECT_SOURCE_DIR}/proto proto_src)

add_executable(grpc_client ${grpc_client_src} ${proto_src})
add_executable(grpc_server ${grpc_server_src} ${proto_src})

target_include_directories(grpc_client PRIVATE ${PROJECT_SOURCE_DIR})
target_include_directories(grpc_server PRIVATE ${PROJECT_SOURCE_DIR})

target_link_libraries(grpc_client PRIVATE gRPC::grpc++)
target_link_libraries(grpc_server PRIVATE gRPC::grpc++)
