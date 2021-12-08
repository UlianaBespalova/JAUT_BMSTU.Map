cmake_minimum_required(VERSION 3.10)

set(PROJECT_NAME BMSTU_Map)

set(SOURCE_DIR src)
set(SOURCE
        ${SOURCE_DIR}/main.cpp
        )

set(LIBS_DIR libs)
set(LIBS
        core
        network
        ui
        )

project(${PROJECT_NAME})

# TODO: Gtest ?

add_executable(${PROJECT_NAME} ${SOURCE})

foreach(LIB ${LIBS})
    add_subdirectory("${LIBS_DIR}/${LIB}")
endforeach(LIB)
target_link_libraries(${PROJECT_NAME} ${LIBS})