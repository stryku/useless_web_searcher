cmake_minimum_required(VERSION 3.8)

project(url_db_lib)

FILE(GLOB_RECURSE SRC  *.*pp)

add_library(${PROJECT_NAME} STATIC ${SRC})

target_include_directories(${PROJECT_NAME} PUBLIC .)
