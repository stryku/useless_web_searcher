cmake_minimum_required(VERSION 3.6)

project(parser_tests)

aux_source_directory(. SRC)

add_executable(${PROJECT_NAME} ${SRC})

message(INFO "${gtest_SOURCE_DIR}/include")

target_include_directories(${PROJECT_NAME} PRIVATE "${gtest_SOURCE_DIR}/include" "${gmock_SOURCE_DIR}/include")

target_link_libraries(${PROJECT_NAME} parser_lib gmock gmock_main)

add_custom_target(RUN_${PROJECT_NAME}
        COMMAND ${PROJECT_NAME}
        COMMENT "Running ${PROJECT_NAME}")