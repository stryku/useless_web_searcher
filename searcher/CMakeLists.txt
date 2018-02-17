cmake_minimum_required(VERSION 3.8)

project(searcher)

add_executable(searcher main.cpp)
target_link_libraries(searcher common)
