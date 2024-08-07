# message(${CMAKE_VERSION})            # 当前 CMake 的版本号
# message(${CMAKE_SOURCE_DIR})         # 顶级源代码目录的路径
# message(${CMAKE_BINARY_DIR})         # 顶层构建目录的路径
# message(${CMAKE_CURRENT_SOURCE_DIR}) # 当前处理的 CMakeLists.txt 文件所在的源代码目录的路径
# message(${CMAKE_CURRENT_BINARY_DIR}) # 当前处理的 CMakeLists.txt 文件所在的二进制目录的路径
# message(${CMAKE_CURRENT_LIST_FILE})  # 当前处理的 CMakeLists.txt 文件的完整路径，包括文件名
# message(${CMAKE_MODULE_PATH})        # 指定额外的模块查找路径的列表
# message(${CMAKE_BUILD_TYPE})         # 当前构建的类型，例如 Debug、Release
# message(${CMAKE_CXX_STANDARD})       # C++ 标准
# message(${CMAKE_C_STANDARD})         # C 标准
# message(${PROJECT_NAME})             # 当前项目名
# message(${RUNTIME_OUTPUT_DIRECTORY})   # 目标文件输出路径
# message(${LIBRARY_OUTPUT_PATH})
# message(${ARCHIVE_OUTPUT_DIRECTORY})


if(APPLE)
    message("Current OS is Apple")
elseif(UNIX)
    message("Current OS is UNIX")
elseif(WIN32)
    message("Current OS is Windows")
else()
    message("Current OS is unknown")
endif()
