cmake_minimum_required(VERSION 3.8)

project(parser_lib)

aux_source_directory(. SRC)

add_library(${PROJECT_NAME} STATIC ${SRC})

target_include_directories(${PROJECT_NAME} PUBLIC .)
