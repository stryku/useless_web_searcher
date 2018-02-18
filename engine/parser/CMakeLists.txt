cmake_minimum_required(VERSION 3.8)

project(parser)

aux_source_directory(. SRC)

add_executable(${PROJECT_NAME} ${SRC})

target_link_libraries(${PROJECT_NAME} parser_lib ${Boost_LIBRARIES} easylogging ${ZMQ_LIBRARIES})
