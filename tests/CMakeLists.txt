cmake_minimum_required(VERSION 3.8)

project(tests)

FILE(GLOB_RECURSE SRC  *.*pp)

add_executable(${PROJECT_NAME} ${SRC})

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} "${gtest_SOURCE_DIR}/include" "${gmock_SOURCE_DIR}/include")

target_link_libraries(${PROJECT_NAME} common gmock_main ${Boost_LIBRARIES} easylogging ${ZMQ_LIBRARIES})
