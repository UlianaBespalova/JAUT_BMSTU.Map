cmake_minimum_required(VERSION 3.20)
project(BMSTU_Map_Core)

add_subdirectory(src)
include_directories(src)

# main
add_executable(core_main main.cpp)
target_link_libraries(core_main BMSTU_Map_Core)


# GTests
find_package(GTest)
if (${GTest_FOUND})
    # found
    include_directories(${GTEST_INCLUDE_DIRS})
else()
    # download
    configure_file(tests/CMakeLists.txt.in googletest-download/CMakeLists.txt)
    execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" . WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download)
    execute_process(COMMAND ${CMAKE_COMMAND} --build . WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download)

    add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src ${CMAKE_BINARY_DIR}/googletest-build)
    set(GTEST_LIBRARIES gtest_main)
endif()

# enable
enable_testing()
find_package(Threads)

add_executable(core_tests tests/main.cpp tests/geometry_test.cpp tests/model_test.cpp tests/view_test.cpp)
target_link_libraries(core_tests ${GTEST_LIBRARIES} pthread BMSTU_Map_Core)
