cmake_minimum_required(VERSION 3.8)

project(common)

FILE(GLOB_RECURSE SRC  *.*pp)

add_library(${PROJECT_NAME} STATIC ${SRC})

target_link_libraries(${PROJECT_NAME} zmq)