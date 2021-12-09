cmake_minimum_required(VERSION 3.15)


set(PROJECT_NAME BMSTU_Map)

set(HEADERS_DIR include/${PROJECT_NAME})
set(HEADERS
        )

set(SOURCE_DIR src)
set(SOURCE
        ${SOURCE_DIR}/main.cpp
        )


set(LIBS_DIR libs)
set(LIBS
        core
        network
        )


project(${PROJECT_NAME})


# TODO: Gtest ?


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


set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

add_library(${LIB_NAME} SHARED ${LIB_HEADERS_FILES} ${LIB_SOURCE_FILES})

# sources & headers
target_include_directories(${LIB_NAME} PRIVATE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/${LIB_NAME}>
        $<INSTALL_INTERFACE:include/${LIB_NAME}>
        )

target_include_directories(${LIB_NAME} PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        )


# Qt5
find_package(QT NAMES Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt5 COMPONENTS Widgets REQUIRED)
target_link_libraries(${LIB_NAME} Qt5::Widgets)


add_subdirectory(tests)

set(CMAKE_AUTOMOC OFF)
# libs
foreach (LIB ${LIBS})
    add_subdirectory("${LIBS_DIR}/${LIB}")
endforeach (LIB)
target_link_libraries(${LIB_NAME} ${LIBS})


add_executable(${PROJECT_NAME} ${SOURCE} ${HEADERS})
target_link_libraries(${PROJECT_NAME} ${LIB_NAME})
