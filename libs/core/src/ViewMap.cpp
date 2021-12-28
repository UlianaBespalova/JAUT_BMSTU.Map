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
const View::Color blue_room = {211,232,255};
const View::Color blue_coridor = {235,235,235};
const View::Color blue_lift = {175,201,244};
const View::Color grey = {241,241,241};

const View::Color path_color = {112, 4, 3};

struct RoomColors {
    View::Color lines;
    View::Color brush;
};

const RoomColors &getColor(const Model::Map::Room &room) {
    using Type = Model::Map::Room::Type;

    static const std::unordered_map<Type, RoomColors> colors = {
            { Type::Unknown, { black, red }},
            { Type::Cabinet, { black, blue_room }},
            { Type::Corridor, { black, blue_coridor }},
            { Type::Stairs, { black, blue_lift }},
            { Type::Elevator, { black, blue_lift }},
    };

    auto item = colors.find(room.type);
    if (item == colors.end()) {  // unsupported type of room
        throw std::runtime_error("Unknown room type while choosing a color!");
    }

    return item->second;
}

void View::Map::drawRoom(const Model::Map::Room &room) {
    if (room.floor != drawer->floor) return;

    // ### Polygon
    RoomColors colors = getColor(room);
    drawer->setLineColor(colors.lines);
    drawer->setBrushColor(colors.brush);

    std::vector<Geometry::Point> points;  // collecting points for polygon
    for (const auto &wall : room.getWalls()) {
        points.push_back(wall.end);
    }
    drawer->drawPolygon(points);


    // ### Text
    Geometry::Point pos = room.start();

    // fixing text pos
    pos.x += 20;
    pos.y += 30;

    std::string text = (room.properties.find("name") != room.properties.end()) ? room.properties.at("name") : std::to_string(room.id);
    drawer->drawText(text, pos);


    // ### Icons  // TODO: rework
    if (room.type == Model::Map::Room::Type::Stairs)
        drawer->drawImage(room.center(), "../media/stair.png");
    if (room.type == Model::Map::Room::Type::Elevator)
        drawer->drawImage(room.center(), "../media/lift.png");

}

void View::Map::setPath(const Path &p)
{
    hasPath = true;
    this->path = p;
}

void View::Map::drawPath(const Path &p)
{
    drawer->setLineColor(path_color);
    for (int i = 1; i < p.size(); ++i) {
        drawer->drawLine(p[i - 1], p[i]);
    }
}
