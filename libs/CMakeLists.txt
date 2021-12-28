cmake_minimum_required(VERSION 3.9)
project(graph)

set(CMAKE_CXX_FLAGS "-g -O0 -Wall -fprofile-arcs -ftest-coverage -pthread -lpqxx -lpq")
set(CMAKE_EXE_LINKER_FLAGS "-fprofile-arcs -ftest-coverage")

set(LIB_SOURCE_DIR src)
set(LIB_HEADERS_DIR include/${LIB_NAME})

include_directories(${PROJECT_SOURCE_DIR}libs)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/graph/config.txt
        ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

add_library(graph STATIC ${PROJECT_SOURCE_DIR}/graph/graph.cpp)
add_library(database STATIC ${PROJECT_SOURCE_DIR}/graph/database.cpp)

enable_testing()

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

find_library(PQXX_LIB pqxx)
find_library(PQ_LIB pq)

add_executable(Graph_test graph/graph_test.cpp)
target_link_libraries(Graph_test database graph ${GTEST_LIBRARIES} ${PQXX_LIB} ${PQ_LIB})
