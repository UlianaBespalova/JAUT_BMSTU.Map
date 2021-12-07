cmake_minimum_required(VERSION 3.10)
project(BMSTU_JAUT_MAP_NETWORK_MAIN)

# boost
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
#set(BOOST_USE_STATIC_LIBS on)
set(BOOST_REQUESTED_VERSION 1.68.0)
find_package(Boost COMPONENTS system asio)


# src
add_subdirectory(src)
include_directories(src)

# server main
add_executable(httpServer_run server_main.cpp)
target_link_libraries(httpServer_run httpServer)
target_link_libraries(httpServer_run ${Boost_LIBRARIES})
target_link_libraries(httpServer_run pthread)

# client main
add_executable(httpClient_run client_main.cpp)
target_link_libraries(httpClient_run httpClient_library ${CMAKE_DL_LIBS})
target_link_libraries(httpClient_run pthread)