#ifndef BMSTU_MAP_CORE_MODEL_MAP_HPP
#define BMSTU_MAP_CORE_MODEL_MAP_HPP

#include <vector>
#include <string>
#include "../misc/geometry.hpp"


namespace Core {
    namespace Model {
        class Map {
            public:
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

            protected:
                std::vector<Room> rooms;
                static std::vector<Room> load(const json& j);

            public:
                explicit Map(const json& j);

                ~Map() = default;
                Map(const Map &) = delete;
                Map &operator=(const Map &) = delete;

                inline const std::vector<Room> &getRooms() { return rooms; };
                inline static const std::vector<Wall> &getWalls(const Room &room) { return room.walls; };
        };

        void from_json(const json &j, Map::Wall &w);
        void from_json(const json &j, Map::Room &r);
    }
}

#endif //BMSTU_MAP_CORE_MODEL_MAP_HPP
