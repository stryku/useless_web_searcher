cmake_minimum_required(VERSION 3.8)

project(index_lib)

FILE(GLOB_RECURSE SRC  *.*pp)

add_library(${PROJECT_NAME} STATIC ${SRC})

target_include_directories(${PROJECT_NAME} PUBLIC .)

target_link_libraries(${PROJECT_NAME} common ${Boost_LIBRARIES} easylogging ${ZMQ_LIBRARIES})
