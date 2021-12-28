#include "ViewMap.hpp"

using namespace Core;

View::Map::Map(Model::Map *_model, View::IDrawer *_drawer) : model(_model), drawer(_drawer), path() { }

void View::Map::drawMap() {
    assert(drawer != nullptr);
    assert(model != nullptr);

    for (const auto &room_pair: model->getRooms()) {
        drawRoom(room_pair.second);
    }
    if (hasPath)
        drawPath(path);
}

const View::Color white = { 255, 255, 255 };
const View::Color black = { 0, 0, 0 };
const View::Color light_gray = { 192, 192, 192 };
const View::Color red = { 255, 0, 0 };
const View::Color green = { 0, 255, 0 };
const View::Color light_green = { 127, 255, 127 };
const View::Color light_blue = { 127, 127, 255 };

struct RoomColors {
    View::Color lines;
    View::Color brush;
};

const RoomColors &getColor(const Model::Map::Room &room) {
    using Type = Model::Map::Room::Type;

    static const std::unordered_map<Type, RoomColors> colors = {
            { Type::Unknown, { black, red }},
            { Type::Cabinet, { black, light_blue }},
            { Type::Corridor, { black, light_gray }},
            { Type::Stairs, { black, light_green }},
            { Type::Elevator, { black, green }},
    };

    auto item = colors.find(room.type);
    if (item == colors.end()) {  // unsupported type of room
        throw std::runtime_error("Unknown room type while choosing a color!");
    }

    return item->second;
}

void View::Map::drawRoom(const Model::Map::Room &room) {
    RoomColors colors = getColor(room);
    drawer->setLineColor(colors.lines);
    drawer->setBrushColor(colors.brush);

    std::vector<Geometry::Point> points;
    Geometry::Point start = room.getWalls().begin()->start;
    for (const auto &wall : room.getWalls()) {
        points.push_back(wall.end);

        for (auto point : { wall.start, wall.end })
            if (point.y <= start.y and point.x <= start.x)
                start = point;
    }

    start.x += 20;
    start.y += 30;

    drawer->drawPolygon(points);

    std::string text = (room.properties.find("name") != room.properties.end()) ? room.properties.at("name") : std::to_string(room.id);
    drawer->drawText(text, start);
}

void View::Map::setPath(const Path &p)
{
    hasPath = true;
    this->path = p;
}

void View::Map::drawPath(const Path &p)
{
    drawer->setLineColor(red);
    for (int i = 1; i < p.size(); ++i) {
        drawer->drawLine(p[i - 1], p[i]);
    }
}
