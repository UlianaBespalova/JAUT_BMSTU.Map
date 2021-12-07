set(UI_SRC
src/mainWindow.cpp
src/drawer.cpp
src/mapController.cpp
)

set(UI_HDR
include/mainWindow.h
include/drawer.h
include/mapController.h
)

add_library(ui STATIC ${UI_SRC} ${UI_HDR})

target_include_directories(ui PUBLIC include)

target_link_libraries(ui PUBLIC Qt5::Widgets)