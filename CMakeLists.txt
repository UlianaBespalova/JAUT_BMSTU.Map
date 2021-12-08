cmake_minimum_required(VERSION 3.15)


set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)


set(PROJECT_NAME BMSTU_Map)

set(HEADERS_DIR include/${PROJECT_NAME})
set(HEADERS
        ${HEADERS_DIR}/drawer.h
        ${HEADERS_DIR}/mainWindow.h
        ${HEADERS_DIR}/mapController.h
        )

set(SOURCE_DIR src)
set(SOURCE
        ${SOURCE_DIR}/main.cpp
        ${SOURCE_DIR}/drawer.cpp
        ${SOURCE_DIR}/mainWindow.cpp
        ${SOURCE_DIR}/mapController.cpp
        )

set(LIBS_DIR libs)
set(LIBS
        core
        network
        )


project(${PROJECT_NAME})


# TODO: Gtest ?


add_executable(${PROJECT_NAME} ${SOURCE} ${HEADERS})

# Qt5
find_package(QT NAMES Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt5 COMPONENTS Widgets REQUIRED)
target_link_libraries(${PROJECT_NAME} Qt5::Widgets)


# libs
foreach (LIB ${LIBS})
    add_subdirectory("${LIBS_DIR}/${LIB}")
endforeach (LIB)
target_link_libraries(${PROJECT_NAME} ${LIBS})


# sources & headers
target_include_directories(${PROJECT_NAME} PRIVATE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}>
        $<INSTALL_INTERFACE:include/${LIB_NAME}>
        )

target_include_directories(${PROJECT_NAME} PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        )
