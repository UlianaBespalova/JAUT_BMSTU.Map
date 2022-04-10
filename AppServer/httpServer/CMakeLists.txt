cmake_minimum_required(VERSION 3.10)
project(httpServer)

set(CMAKE_CXX_STANDARD 14)

include_directories(../baseClasses ../httpClient managers)

add_definitions(-DBOOST_ERROR_CODE_HEADER_ONLY)

set(BOOST_ROOT /usr/local/lib/boost_1_68_0)
set(BOOST_LYBRARYDIR /usr/local/lib/boost_1_68_0/stage/lib)

find_package(Boost 1.68.0 REQUIRED)
set(Boost_USE_STATIC_LIBS        ON)
set(Boost_USE_MULTITHREADED      ON)


if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})

#    add_library(types INTERFACE)
#    target_include_directories(types INTERFACE managers/types.h)
#    target_link_libraries(types INTERFACE ${Boost_LIBRARIES})

    add_library(httpServer httpServer.cpp httpServerConnection.cpp router.cpp)
    add_library(bitopManager managers/bitopManager.cpp ../httpClient/httpClient.cpp ../httpClient/httpClientConnection.cpp)
    add_library(mapManager managers/mapManager.cpp)
    add_library(cacheManager managers/cacheManager.cpp)

    target_link_libraries(httpServer bitopManager mapManager cacheManager)

    add_executable(httpServer_run main.cpp)
    target_link_libraries(httpServer_run httpServer)
    target_link_libraries(httpServer_run ${Boost_LIBRARIES})
    target_link_libraries(httpServer_run pthread)
endif()
