cmake_minimum_required(VERSION 3.6)

project(common_test)

aux_source_directory(. SRC)

add_executable(${PROJECT_NAME} ${SRC})

target_link_libraries(${PROJECT_NAME} gmock gmock_main common)
