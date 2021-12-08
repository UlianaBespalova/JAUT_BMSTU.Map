cmake_minimum_required(VERSION 3.20)

set(PROJECT_NAME BMSTU_Map_Core)
set(LIB_NAME core)

set(LIB_SOURCE_DIR src)
set(LIB_HEADERS_DIR include/${LIB_NAME})

set(LIB_HEADERS_FILES
        ${LIB_HEADERS_DIR}/core.hpp
        ${LIB_HEADERS_DIR}/utils.hpp
        ${LIB_HEADERS_DIR}/geometry.hpp
        ${LIB_HEADERS_DIR}/ModelMap.hpp
        ${LIB_HEADERS_DIR}/ViewMap.hpp
        )

set(LIB_SOURCE_FILES
        ${LIB_SOURCE_DIR}/core.cpp
        ${LIB_SOURCE_DIR}/ModelMap.cpp
        ${LIB_SOURCE_DIR}/ViewMap.cpp
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

# Boost
#find_package(Boost REQUIRED COMPONENTS json)
#include_directories(${Boost_INCLUDE_DIR})


# JSON
find_package(nlohmann_json QUIET)
if (NOT ${nlohmann_json_FOUND})
    # download
    include(FetchContent)

    FetchContent_Declare(json
            GIT_REPOSITORY https://github.com/nlohmann/json.git
            GIT_TAG v3.10.4)

    FetchContent_GetProperties(json)
    if (NOT json_POPULATED)
        FetchContent_Populate(json)
        add_subdirectory(${json_SOURCE_DIR} ${json_BINARY_DIR} EXCLUDE_FROM_ALL)
    endif ()
endif ()
target_link_libraries(${LIB_NAME} nlohmann_json::nlohmann_json)


# main
set(MAIN_NAME ${LIB_NAME}_main)
add_executable(${MAIN_NAME} main.cpp)
target_link_libraries(${MAIN_NAME} ${LIB_NAME})

# tests
add_subdirectory(tests)
