#include "ModelMap.hpp"

using namespace Core;

const std::string by_floors = "floors";
const std::string by_rooms = "rooms";
const std::string key_floor = "floor";
const std::string key_rooms = "rooms";

std::vector<Model::Map::Room> Model::Map::load(const json &j)
{
    std::vector<Room> rooms;
    // rooms by floors
    if (j.contains(by_floors))
        for (auto &json_floor: j.at(by_floors)) {
            int floor = json_floor.at(key_floor);

            for (auto &json_room : json_floor.at(key_rooms)) {
                auto room = json_room.get<Room>();
                room.floor = floor;
                rooms.push_back(room);
            }
        }

    // remaining rooms
    if (j.contains(by_rooms))
        for (auto &json_room: j.at(by_rooms))
            rooms.push_back(json_room.get<Room>());
    return rooms;
}

Model::Map::Map(const json &j) : rooms(load(j)) { }


const std::string wall_type = "type";
const std::string wall_start = "start";
const std::string wall_end = "end";

void Model::from_json(const json &j, Map::Wall &w)
{
    if (j.contains(wall_type)) j.at(wall_type).get_to(w.type);
    j.at(wall_start).get_to(w.start);
    j.at(wall_end).get_to(w.end);
}


const std::string room_walls = "walls";
const std::string room_floor = "floor";
const std::string room_type = "type";
const std::string room_properties = "properties";

void Model::from_json(const json &j, Model::Map::Room &r)
{
    for (auto &jw: j.at(room_walls))
        r.walls.push_back(jw.get<Map::Wall>());

    if (j.contains(room_floor))
        j.at(room_floor).get_to(r.floor);

    if (j.contains(room_type))
        j.at(room_type).get_to(r.type);

    if (j.contains(room_properties))
        for (auto &el: j.at(room_properties).items())
            r.properties[el.key()] = el.value();
}