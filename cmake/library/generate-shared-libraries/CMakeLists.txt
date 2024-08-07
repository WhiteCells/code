cmake_minimum_required(VERSION 3.20.0)

project(generate-libraries CXX)

# 添加 include 包含目录，以便编译器可以在该目录中查找头文件
include_directories(${PROJECT_SOURCE_DIR}/include)

# 设置库的输出路径
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

# 根据指定的通配符模式获取文件列表
file(GLOB SRC ${PROJECT_SOURCE_DIR}/src/*.cpp)

# 创建一个动态库，将指定源文件添加到该库中
add_library(test1 SHARED ${SRC})