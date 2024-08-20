#!/bin/bash

set -e

rm ./*.pb.cc ./*.pb.h -fv

protoc \
-I=. \
--cpp_out=. \
login.proto

echo "generate finished"