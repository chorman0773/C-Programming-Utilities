project(collect C)
cmake_minimum_required(VERSION 3.10)

include_directories(include)

add_library(collect SHARED include/List.h include/Map.h src/List.c src/Map.c)
