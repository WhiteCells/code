cmake_minimum_required(VERSION 3.28)

project(modules_test LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(modules_test)

target_sources(modules_test
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/auth_impl.cc"
        "${CMAKE_CURRENT_SOURCE_DIR}/main.cc"
    PRIVATE
        FILE_SET cxx_modules TYPE CXX_MODULES
        FILES "${CMAKE_CURRENT_SOURCE_DIR}/auth.cppm"
)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    message("STATUS" "Use GNU")
    target_compile_options(modules_test PRIVATE -fmodules-ts)
elseif(NOT CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    message(FATAL_ERROR "Unsupported compiler: ${CMAKE_CXX_COMPILER_ID}. Use GCC or Clang.")
endif()

add_custom_target(run
    COMMAND "$<TARGET_FILE:modules_test>"
    DEPENDS modules_test
    USES_TERMINAL
)
