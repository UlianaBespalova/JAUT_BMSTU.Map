cmake_minimum_required(VERSION 3.10)
project(httpClient)

set(CMAKE_CXX_STANDARD 14)

include_directories(httpClient)

add_definitions(-DBOOST_ERROR_CODE_HEADER_ONLY)

set(BOOST_ROOT /usr/local/lib/boost_1_68_0)
set(BOOST_LYBRARYDIR /usr/local/lib/boost_1_68_0/stage/lib)

find_package(Boost 1.68.0 REQUIRED)
set(Boost_USE_STATIC_LIBS        ON)
set(Boost_USE_MULTITHREADED      ON)

if(Boost_FOUND)

    include_directories(${Boost_INCLUDE_DIRS})

    set(LIB_DIR httpClient)
    set(LIB_SOURCE_FILES ${LIB_DIR}/httpClient.cpp)
    add_library(httpClient SHARED ${LIB_SOURCE_FILES})
    target_include_directories(httpClient PUBLIC ${Boost_LIBRARIES})

#-------------------------
#add_library(httpClient httpClient.cpp httpClientConnection.cpp)

    add_executable(httpClient_run main.cpp)
    target_link_libraries(httpClient_run httpClient ${CMAKE_DL_LIBS})
    target_link_libraries(httpClient_run pthread)
    target_link_libraries(httpClient_run ssl)
    target_link_libraries(httpClient_run crypto)
endif()


