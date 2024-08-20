cmake_minimum_required(VERSION 3.5)

project(server)

aux_source_directory(./ src)

add_executable(server ${src})