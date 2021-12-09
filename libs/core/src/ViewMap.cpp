#include "ViewMap.hpp"

using namespace Core;

View::Map::Map(Model::Map *_model, View::IDrawer *_drawer) : model(_model), drawer(_drawer), path() { }

void View::Map::drawMap() {
    assert(drawer != nullptr);
    assert(model != nullptr);

    for (const auto &room: model->getRooms()) {
        drawRoom(room);
    }
    if (hasPath)
        drawPath(path);
}

void View::Map::drawRoom(const Model::Map::Room &room) {
    switch (room.type) {
        case Model::Map::Room::Type::Unknown:drawer->setColor({ 255, 0, 0 });
            break;
        case Model::Map::Room::Type::Cabinet:drawer->setColor({ 0, 0, 0 });
            break;
        case Model::Map::Room::Type::Corridor:drawer->setColor({ 255, 0, 0 });
            break;
        case Model::Map::Room::Type::Stairs:drawer->setColor({ 127, 255, 127 });
            break;
        case Model::Map::Room::Type::Elevator:drawer->setColor({ 0, 255, 0 });
            break;
        default:
#ifndef NDEBUG
            throw std::runtime_error("Unknown _color!");
#endif
            break;
    }

    for (const auto &wall: Model::Map::getWalls(room)) {
        drawWall(wall);
    }
}

void View::Map::drawWall(const Model::Map::Wall &wall) {
    drawer->drawLine(wall.start, wall.end);
}

void View::Map::setPath(const Path &p)
{
    hasPath = true;
    this->path = p;
}

void View::Map::drawPath(const Path &p)
{
    drawer->setColor({ 255, 0, 0 });
    for (int i = 1; i < p.size(); ++i) {
        drawer->drawLine(p[i - 1], p[i]);
    }
}
