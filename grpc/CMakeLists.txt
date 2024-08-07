cmake_minimum_required(VERSION 3.5)

project(grpc-example LANGUAGES CXX VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Protobuf CONFIG REQUIRED)
find_package(gRPC CONFIG REQUIRED)

aux_source_directory(${PROJECT_SOURCE_DIR} src)

add_executable(grpc-example ${src})

target_link_libraries(grpc-example PRIVATE 
    gRPC::grpc++_reflection
    protobuf::libprotobuf
    gRPC::grpc++
)