cmake_minimum_required(VERSION 3.8)

project(index)

FILE(GLOB_RECURSE SRC  *.*pp)

add_executable(${PROJECT_NAME} ${SRC})

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME} common index_lib ${Boost_LIBRARIES} easylogging ${ZMQ_LIBRARIES})
