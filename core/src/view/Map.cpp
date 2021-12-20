#include "Map.hpp"

using namespace Core;

void View::Map::drawMap() {
    assert(drawer != nullptr);
    assert(model != nullptr);

    for (const auto &room: model->getRooms()) {
        drawRoom(room);
    }
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
