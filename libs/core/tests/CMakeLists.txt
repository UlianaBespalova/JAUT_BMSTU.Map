cmake_minimum_required(VERSION 3.15)

set(TEST_PROJECT_NAME
        ${LIB_NAME}_tests
        )

set(LIB_TESTS_SOURCE
        main.cpp
        model_test.cpp
        geometry_test.cpp
        view_test.cpp
        )

project(${TEST_PROJECT_NAME})


# GTests
find_package(GTest REQUIRED)
find_package(Threads)
include_directories(${GTEST_INCLUDE_DIRS})

enable_testing()

add_executable(${TEST_PROJECT_NAME} ${LIB_TESTS_SOURCE})
target_link_libraries(${TEST_PROJECT_NAME}
        gtest
        gtest_main
        pthread
        ${LIB_NAME}
        )
