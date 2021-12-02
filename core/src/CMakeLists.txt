cmake_minimum_required(VERSION 3.20)
project(BMSTU_Map_Core)

set(CMAKE_CXX_STANDARD 17)


# Core lib
set(LIB_HEADERS_FILES
        core.hpp
        misc/utils.hpp
        misc/geometry.hpp
        model/Map.hpp
        view/Map.hpp
        network/NetManager.hpp
        )
set(LIB_SOURCE_FILES
        core.cpp
        model/Map.cpp
        view/Map.cpp
        )

add_library(BMSTU_Map_Core SHARED ${LIB_HEADERS_FILES} ${LIB_SOURCE_FILES})


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

target_link_libraries(BMSTU_Map_Core nlohmann_json::nlohmann_json)
