#include "ModelMap.hpp"

using namespace Core;


Model::Map::Map(const json &j) { //}, graph() {
    const static std::string by_floors = "floors";
    const static std::string key_floor = "floor";
    const static std::string key_rooms = "rooms";

    // rooms by floors
    for (auto &json_floor: j.at(by_floors)) {
        int floor = json_floor.at(key_floor);

        for (auto &json_room: json_floor.at(key_rooms)) {
            auto room = json_room.get<Room>();
            room.floor = floor;
            rooms[room.id] = room;
            graph.add_top(room.id);
        }

        for (auto &json_room: json_floor.at(key_rooms)) {
            auto room = json_room.get<Room>();
            for (auto &to_room : json_room.at("connected"))
                graph.add_edge(room.id, to_room.get<id_t>(), 1);
        }
    }
}

// JSON format: [ x, y, * type ]
void Model::from_json(const json &j, Map::Wall &w)
{
    j.at(0).get_to(w.start);
    j.at(1).get_to(w.end);
    if (j.size() > 2) j.at(2).get_to(w.type);
}

/* JSON format:
{
    "id": unsigned int,
    "walls": [ Map::Wall ],
 *  "type": Map::Wall,
 *  "floor": int,
 *  "properties" : { ... }
}
 */
void Model::from_json(const json &j, Model::Map::Room &r)
{
    const static std::string room_id = "id";
    const static std::string room_type = "type";
    const static std::string room_floor = "floor";
    const static std::string room_walls = "walls";
    const static std::string room_properties = "properties";

    j.at(room_id).get_to(r.id);

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