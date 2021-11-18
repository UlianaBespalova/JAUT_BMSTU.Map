set(CMAKE_INCLUDE_CURRENT_DIR ON)
cmake_minimum_required(VERSION 3.10)
project(UI)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5Widgets)
find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets Multimedia REQUIRED)

file(GLOB PROJECT_SOURCES "./*.cpp")

add_library(UI ${PROJECT_SOURCES} )
target_link_libraries(UI
                      Qt${QT_VERSION_MAJOR}::Widgets
                      )