#ifndef BMSTU_MAP_CORE_MODEL_MAP_HPP
#define BMSTU_MAP_CORE_MODEL_MAP_HPP

#include <vector>
#include <string>
#include "../misc/geometry.hpp"


namespace Core {
    namespace Model {
        struct Wall {
            enum Type { Solid, Pass, Door } type = Solid;
            Geometry::Point start = { }, end = { };
        };

        struct Room {
            enum Type { Unknown, Cabinet, Corridor, Stairs, Elevator } type = Unknown;
            int floor = 0;
            std::vector<Wall> walls = { };
            std::unordered_map<std::string, std::string> properties;
        };

        // region from_json
        inline void from_json(const json &j, Wall &w)
        {
            if (j.contains("type")) j.at("type").get_to(w.type);
            j.at("start").get_to(w.start);
            j.at("end").get_to(w.end);
        }

        inline void from_json(const json &j, Room &r)
        {
            for (auto &jw: j.at("walls"))
                r.walls.push_back(jw.get<Wall>());

            if (j.contains("floor"))
                j.at("floor").get_to(r.floor);

            if (j.contains("type"))
                j.at("type").get_to(r.type);

            if (j.contains("properties"))
                for (auto &el: j.at("properties").items())
                    r.properties[el.key()] = el.value();
        }
        // endregion

        class Map {
            protected:
                static std::vector<Room> load(const json& j) {
                        std::vector<Room> rooms;
                        // rooms by floors
                        if (j.contains("floors"))
                            for (auto &json_floor : j.at("floors")) {
                                int floor = json_floor.at("floor");

                                for (auto &json_room : json_floor.at("rooms")) {
                                    auto room = json_room.get<Room>();
                                    room.floor = floor;
                                    rooms.push_back(room);
                                }
                            }

                        // remaining rooms
                        if (j.contains("rooms"))
                            for (auto &json_room : j.at("rooms"))
                                rooms.push_back(json_room.get<Room>());
                        return rooms;
                }

            public:
                explicit Map(const json& j) : rooms(load(j)) { }
                ~Map() = default;

                inline const std::vector<Room> &getRooms() { return rooms; };
                inline static const std::vector<Wall> &getWalls(const Room &room) { return room.walls; };

            protected:
                std::vector<Room> rooms;
        };
    }
}

#endif //BMSTU_MAP_CORE_MODEL_MAP_HPP
