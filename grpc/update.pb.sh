#!/bin/bash

set -e

# 指定 .proto 文件所在目录
# 指定输出目录
# 指定使用插件
# 指定编译文件
protoc \
-I=. \
--cpp_out=. \
--plugin=protoc-gen-grpc=`which grpc_cpp_plugin` \
message.proto