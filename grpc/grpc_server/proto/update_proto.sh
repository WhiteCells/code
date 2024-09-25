#!/bin/bash

set -e

rm ./*.pb.cc ./*.pb.h -fv

proto_file="./node.proto"
out_path="./"

protoc \
-I=. \
--cpp_out=$out_path \
--grpc_out=$out_path \
--plugin=protoc-gen-grpc=`which grpc_cpp_plugin` \
$proto_file