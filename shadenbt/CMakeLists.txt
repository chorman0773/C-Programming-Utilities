project(shadenbt C)

cmake_minimum_required(VERSION 3.10)

include_directories(include ../io/include ../collect/include ../time/include)

add_library(shadenbt SHARED include/NBT.h include/ShadeConstants.h include/ShadeNBT.h src/NBT.c src/ShadeNBT.c)
