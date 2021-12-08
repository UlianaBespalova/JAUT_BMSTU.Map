cmake_minimum_required(VERSION 3.10)
project(UIClient)


add_subdirectory(src)
include_directories(src)


find_package(QT NAMES Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(ui_main main.cpp)
target_link_libraries(ui_main Qt5::Widgets UIClient)

# GTests
find_package(GTest)
if (${GTest_FOUND})
    include_directories(${GTEST_INCLUDE_DIRS})
else()
    configure_file(tests/CMakeLists.txt.in googletest-download/CMakeLists.txt)
    execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" . WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download)
    execute_process(COMMAND ${CMAKE_COMMAND} --build . WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download)

    add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src ${CMAKE_BINARY_DIR}/googletest-build)
    set(GTEST_LIBRARIES gtest_main)
endif()

enable_testing()

add_executable(ui_test tests/test.cpp)

target_link_libraries(ui_test ${GTEST_LIBRARIES} UIClient)
target_link_libraries(ui_test gmock)