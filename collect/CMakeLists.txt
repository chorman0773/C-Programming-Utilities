project(collect C)
cmake_minimum_required(VERSION 3.10)



add_library(collect SHARED include/List.h include/Map.h src/List.c src/Map.c)

target_include_directories(collect PUBLIC include)

install(TARGETS collect)
install(DIRECTORY include/ DESTINATION include FILES_MATCHING PATTERN "*.h")
