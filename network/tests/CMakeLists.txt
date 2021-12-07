cmake_minimum_required(VERSION 3.10)
project(tests)

set(CMAKE_CXX_STANDARD 14)

include_directories(../AppServer/httpClient ../AppServer/httpServer ../AppServer/httpServer/managers
        ../AppServer/baseClasses)

add_definitions(-DBOOST_ERROR_CODE_HEADER_ONLY)

set(BOOST_ROOT /usr/local/lib/boost_1_68_0)
set(BOOST_LYBRARYDIR /usr/local/lib/boost_1_68_0/stage/lib)

find_package(Boost 1.68.0 REQUIRED)
set(Boost_USE_STATIC_LIBS        ON)
set(Boost_USE_MULTITHREADED      ON)

enable_testing()
find_package(GTest REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(tests tests.cpp)
target_link_libraries(tests ${GTEST_LIBRARIES} m pthread)
target_link_libraries(tests gmock)
target_link_libraries(tests ${Boost_LIBRARIES})
