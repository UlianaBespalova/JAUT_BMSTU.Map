#include "Map.hpp"

using namespace Core;

std::vector<Model::Map::Room> Model::Map::load(const json &j)
{
    std::vector<Room> rooms;
    // rooms by floors
    if (j.contains("floors"))
        for (auto &json_floor: j.at("floors")) {
            int floor = json_floor.at("floor");

            for (auto &json_room: json_floor.at("rooms")) {
                auto room = json_room.get<Room>();
                room.floor = floor;
                rooms.push_back(room);
            }
        }

    // remaining rooms
    if (j.contains("rooms"))
        for (auto &json_room: j.at("rooms"))
            rooms.push_back(json_room.get<Room>());
    return rooms;
}

Model::Map::Map(const json &j) : rooms(load(j)) { }

void Model::from_json(const json &j, Map::Wall &w)
{
    if (j.contains("type")) j.at("type").get_to(w.type);
    j.at("start").get_to(w.start);
    j.at("end").get_to(w.end);
}

void Model::from_json(const json &j, Model::Map::Room &r)
{
    for (auto &jw: j.at("walls"))
        r.walls.push_back(jw.get<Map::Wall>());

    if (j.contains("floor"))
        j.at("floor").get_to(r.floor);

    if (j.contains("type"))
        j.at("type").get_to(r.type);

    if (j.contains("properties"))
        for (auto &el: j.at("properties").items())
            r.properties[el.key()] = el.value();
}