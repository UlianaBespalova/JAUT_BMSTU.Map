#include "mapController.h"

MapController::MapController() {
    drawer = new Drawer();
}

bool MapController::setFloor(int newfloor) {
    drawer->setFloor(newfloor);
    return true;
}

bool MapController::scale(double newScale) {
    drawer->setScale(newScale);
    return true;
}

bool MapController::viewMoveBy(QPoint shift) {
    Point new_pos;
    new_pos.x = shift.x();
    new_pos.y = shift.y();
    drawer->setViewPos(new_pos);
    return true;
}