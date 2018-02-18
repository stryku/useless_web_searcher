cmake_minimum_required(VERSION 3.8)

project(url_db)

FILE(GLOB_RECURSE SRC  *.*pp)

add_executable(${PROJECT_NAME} ${SRC})

target_link_libraries(${PROJECT_NAME} common url_db_lib easylogging ${Boost_LIBRARIES})
