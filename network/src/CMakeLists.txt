cmake_minimum_required(VERSION 3.10)
project(BMSTU_JAUT_MAP_NETWORK)

set(CMAKE_CXX_STANDARD 14)

include_directories(baseClasses httpClient httpServer httpServer/managers)

add_definitions(-DBOOST_ERROR_CODE_HEADER_ONLY)

# find_package(Boost COMPONENTS system asio)
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)


if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})

    # server
    add_library(httpServer SHARED
            httpServer/httpServer.h
            httpServer/httpServer.cpp
            httpServer/httpServerConnection.h
            httpServer/httpServerConnection.cpp
            httpServer/router.h
            httpServer/router.cpp
            )
    add_library(bitopManager
            httpServer/managers/bitopManager.h
            httpServer/managers/bitopManager.cpp
            httpClient/httpClient.h
            httpClient/httpClient.cpp
            )
    add_library(mapManager
            httpServer/managers/mapManager.h
            httpServer/managers/mapManager.cpp
            )
    add_library(cacheManager
            httpServer/managers/cacheManager.h
            httpServer/managers/cacheManager.cpp
            )

    target_link_libraries(httpServer bitopManager mapManager cacheManager)

    # client
    add_library(httpClient_library SHARED
            httpClient/httpClient.h
            httpClient/httpClient.cpp
            )
    target_include_directories(httpClient_library PUBLIC ${Boost_LIBRARIES})
endif ()
