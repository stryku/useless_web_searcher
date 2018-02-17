cmake_minimum_required(VERSION 3.8)

project(parse_frontier)

aux_source_directory(. SRC)

add_executable(${PROJECT_NAME} ${SRC})

target_link_libraries(${PROJECT_NAME})
