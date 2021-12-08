cmake_minimum_required(VERSION 3.10)


set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)


set(PROJECT_NAME BMSTU_Map_UI)
set(LIB_NAME ui)

set(LIB_SOURCE_DIR src)
set(LIB_HEADERS_DIR include/${LIB_NAME})

set(LIB_HEADERS_FILES
        ${LIB_HEADERS_DIR}/drawer.h
        ${LIB_HEADERS_DIR}/mainWindow.h
        ${LIB_HEADERS_DIR}/mapController.h
        )

set(LIB_SOURCE_FILES
        ${LIB_SOURCE_DIR}/drawer.cpp
        ${LIB_SOURCE_DIR}/mainWindow.cpp
        ${LIB_SOURCE_DIR}/mapController.cpp
        )

project(${PROJECT_NAME})
add_library(${LIB_NAME} SHARED ${LIB_HEADERS_FILES} ${LIB_SOURCE_FILES})


target_include_directories(${LIB_NAME} PRIVATE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/${LIB_NAME}>
        $<INSTALL_INTERFACE:include/${LIB_NAME}>
        )

target_include_directories(${LIB_NAME} PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        )

find_package(QT NAMES Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt5 COMPONENTS Widgets REQUIRED)
target_link_libraries(${LIB_NAME} Qt5::Widgets)


# main
set(MAIN_NAME ${LIB_NAME}_main)
add_executable(${MAIN_NAME} main.cpp)
target_link_libraries(${MAIN_NAME} ${LIB_NAME})

# tests
add_subdirectory(tests)
