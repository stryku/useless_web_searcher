cmake_minimum_required(VERSION 3.8)

project(easylogging)

aux_source_directory(. SRC)

add_library(${PROJECT_NAME} STATIC ${SRC})
