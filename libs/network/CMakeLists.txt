cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 14)

set(PROJECT_NAME BMSTU_Map_Network)
set(LIB_NAME network)

set(LIB_SOURCE_DIR src)
set(LIB_HEADERS_DIR include/${LIB_NAME})

set(LIB_HEADERS_FILES
#        ${LIB_HEADERS_DIR}/baseConnection.h
        ${LIB_HEADERS_DIR}/types.h
#        ${LIB_HEADERS_DIR}/bitopManager.h
#        ${LIB_HEADERS_DIR}/cacheManager.h
#        ${LIB_HEADERS_DIR}/mapManager.h
#        ${LIB_HEADERS_DIR}/router.h
        ${LIB_HEADERS_DIR}/httpClient.h
#        ${LIB_HEADERS_DIR}/httpServer.h
        )

set(LIB_SOURCE_FILES
#        ${LIB_SOURCE_DIR}/baseConnection.cpp
#        ${LIB_SOURCE_DIR}/bitopManager.cpp
#        ${LIB_SOURCE_DIR}/cacheManager.cpp
#        ${LIB_SOURCE_DIR}/mapManager.cpp
#        ${LIB_SOURCE_DIR}/router.cpp
        ${LIB_SOURCE_DIR}/httpClient.cpp
#        ${LIB_SOURCE_DIR}/httpServer.cpp
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


add_definitions(-DBOOST_ERROR_CODE_HEADER_ONLY)


# boost
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
set(BOOST_REQUESTED_VERSION 1.68.0)

find_package(Threads)
target_link_libraries(${LIB_NAME} pthread)

find_package(Boost COMPONENTS system asio)
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
include_directories(${Boost_INCLUDE_DIRS})


# main
set(MAIN_NAME ${LIB_NAME}_main)
add_executable(${MAIN_NAME} client_main.cpp)
target_link_libraries(${MAIN_NAME} ${LIB_NAME})

# tests
add_subdirectory(tests)
