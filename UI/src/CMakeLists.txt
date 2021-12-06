cmake_minimum_required(VERSION 3.10)

project(UIClient)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)

set(UI_SRC
mainWindow.cpp
drawer.cpp
mapController.cpp
)

set(UI_HDR
mainWindow.h
drawer.h
mapController.h
)

add_library(UIClient SHARED ${UI_SRC} ${UI_HDR})


find_package(QT NAMES Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt5 COMPONENTS Widgets REQUIRED)



target_link_libraries(UIClient Qt5::Widgets)
