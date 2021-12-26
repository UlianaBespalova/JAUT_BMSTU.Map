cmake_minimum_required(VERSION 3.10)
project(httpServer)

set(CMAKE_CXX_STANDARD 17)

include_directories(managers ../httpClient/httpClient ../../DataBase)

add_definitions(-DBOOST_ERROR_CODE_HEADER_ONLY)

set(PQXX /usr/local/include/pqxx)

find_library(PQXX_LIB pqxx)
find_library(PQ_LIB pq)

set(BOOST_ROOT /usr/local/lib/boost_1_68_0)
set(BOOST_LYBRARYDIR /usr/local/lib/boost_1_68_0/stage/lib)

find_package(Boost 1.68.0 REQUIRED)
set(Boost_USE_STATIC_LIBS        ON)
set(Boost_USE_MULTITHREADED      ON)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})

    add_library(httpServer httpServer.cpp httpServerConnection.cpp router.cpp)
    add_library(cacheManager managers/cacheManager.cpp)
    add_library(bitopManager managers/bitopManager.cpp ../httpClient/httpClient/httpClient.cpp)
    target_link_libraries(bitopManager ssl)
    target_link_libraries(bitopManager crypto)

    add_library(mapManager managers/mapManager.cpp ../../DataBase/graph/database.cpp)
    target_link_libraries(mapManager ${PQXX_LIB} ${PQ_LIB})

    target_link_libraries(httpServer bitopManager mapManager cacheManager)

    add_executable(httpServer_run main.cpp)
    target_link_libraries(httpServer_run httpServer)
    target_link_libraries(httpServer_run ${Boost_LIBRARIES})
    target_link_libraries(httpServer_run pthread)
endif()
