cmake_minimum_required(VERSION 3.8)

project(useless_web_searcher)

set(CMAKE_PREFIX_PATH ~/Qt/5.8/gcc_64)

add_definitions(-fPIC)

find_package (Qt5Widgets)
find_package (Qt5UiTools REQUIRED)

set (QT_SOURCES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/gui/useless_web_searcher)

include_directories (${QT_SOURCES_DIR} ${Qt5UiTools_INCLUDE_DIRS})

set (src_qt ${QT_SOURCES_DIR}/main.cpp
            ${QT_SOURCES_DIR}/mainwindow.cpp)

set (inc_qt ${QT_SOURCES_DIR}/mainwindow.h)

set (hdr ${QT_SOURCES_DIR}/mainwindow.h)
set (ui  ${QT_SOURCES_DIR}/mainwindow.ui)
set (gui_src ${QT_SOURCES_DIR}/main.cpp)
qt5_wrap_cpp(hdr_moc ${hdr})
qt5_wrap_ui (ui_moc  ${ui})

add_library (MocObjects OBJECT 
    ${hdr_moc}
    ${ui_moc}  
)


add_executable(${PROJECT_NAME} ${gui_src} ${src_qt} ${inc_qt} $<TARGET_OBJECTS:MocObjects>)
                                   
target_link_libraries (${PROJECT_NAME} common easylogging  Qt5::Widgets Qt5::UiTools)

