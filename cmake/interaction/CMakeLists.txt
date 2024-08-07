cmake_minimum_required(VERSION 3.20.0)

project(interaction CXX)

set(CMAKE_CXX_STANDARD 11)

# 严格遵循指定的 C++ 标准
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# 生成配置文件
# 将 config.h.in 文件中的变量替换为 CMake 中定义的值，并将结果输出到 config.h 文件中
configure_file(config.h.in config.h)

# 定义可执行文件或库的名称和源文件列表
add_executable(app main.cpp)

# 指定可执行文件或库所需的头文件目录
target_include_directories(app PUBLIC ${PROJECT_BINARY_DIR})