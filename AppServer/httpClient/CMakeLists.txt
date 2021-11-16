cmake_minimum_required(VERSION 3.10)
project(httpClient)

set(CMAKE_CXX_STANDARD 14)

include_directories(../baseClasses)

add_definitions(-DBOOST_ERROR_CODE_HEADER_ONLY)

set(BOOST_ROOT /usr/local/lib/boost_1_68_0)
set(BOOST_LYBRARYDIR /usr/local/lib/boost_1_68_0/stage/lib)

find_package(Boost 1.68.0 REQUIRED)
set(Boost_USE_STATIC_LIBS        ON)
set(Boost_USE_MULTITHREADED      ON)

if(Boost_FOUND)

    include_directories(${Boost_INCLUDE_DIRS})

    add_library(httpClient httpClient.cpp httpClientConnection.cpp)

    add_executable(httpClient_run main.cpp)
    target_link_libraries(httpClient_run httpClient)
    target_link_libraries(httpClient_run ${Boost_LIBRARIES})
    target_link_libraries(httpClient_run pthread)
endif()
