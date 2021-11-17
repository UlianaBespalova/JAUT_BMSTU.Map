cmake_minimum_required(VERSION 3.9)
project(graph)

SET(CMAKE_CXX_FLAGS "-g -O0 -Wall -fprofile-arcs -ftest-coverage -pthread")
SET(CMAKE_EXE_LINKER_FLAGS "-fprofile-arcs -ftest-coverage")

include_directories(${PROJECT_SOURCE_DIR}/res)

add_library(graph STATIC ${PROJECT_SOURCE_DIR}/graph.cpp)

enable_testing()

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(Graph_test graph_test.cpp)
target_link_libraries(Graph_test graph ${GTEST_LIBRARIES})
