cmake_minimum_required(VERSION 3.9)

set(LIB_NAME common)

project(${LIB_NAME})

add_subdirectory(test)

aux_source_directory(. SRC)

add_library(${LIB_NAME} STATIC ${SRC})

target_include_directories(${LIB_NAME} PUBLIC .)
