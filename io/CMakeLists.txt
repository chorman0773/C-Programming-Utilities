project(io C)
cmake_minimum_required(VERSION 3.10)

include_directories(include ../time/include)

add_library(io SHARED include/BinaryIO.h include/Stream.h src/BasicStream.c src/BinaryIO.c src/BufferStream.c src/FileStream.c src/IOStream.c)
