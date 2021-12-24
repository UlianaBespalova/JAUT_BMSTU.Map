#include "mapController.h"

MapController::MapController() {
    drawer = new Drawer();
}

MapController::~MapController() {
    delete drawer;
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
    Point pos = drawer->getViewPos();
    pos.x += shift.x();
    pos.y += shift.y();
    drawer->setViewPos(pos);
    return true;
}
