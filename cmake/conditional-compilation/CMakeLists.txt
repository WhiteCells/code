cmake_minimum_required(VERSION 3.20.0)
project(conditional-compilation CXX)

# include_directories(${PROJECT_SOURCE_DIR}/include)

add_subdirectory(src)

add_executable(app main.cpp)

target_link_libraries(app PUBLIC libtest)

target_include_directories(app PUBLIC ${PROJECT_SOURCE_DIR}/include)