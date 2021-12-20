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

const View::Color red = { 255, 0, 0 };
const View::Color black = { 255, 0, 0 };
const View::Color light_green = { 127, 255, 127 };
const View::Color green = { 0, 255, 0 };

const View::Color &getColor(const Model::Map::Room &room) {
    using Type = Model::Map::Room::Type;
    switch (room.type) {
        case Type::Unknown:  //
            return red;
        case Type::Cabinet:
            return black;
        case Type::Corridor:
            return red;
        case Type::Stairs:
            return light_green;
        case Type::Elevator:
            return green;
        default:
#ifndef NDEBUG
            throw std::runtime_error("Unknown type while choosing a color!");
#endif
            break;
    }
}

void View::Map::drawRoom(const Model::Map::Room &room) {
    drawer->setColor(getColor(room));

    for (const auto &wall : room.getWalls()) {
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
