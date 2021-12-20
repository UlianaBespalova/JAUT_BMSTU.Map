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
                    enum class Type { Solid, Pass, Door } type = Type::Solid;
                    Geometry::Point start = { }, end = { };
                };

                struct Room {
                    enum class Type { Unknown, Cabinet, Corridor, Stairs, Elevator } type = Type::Unknown;
                    int floor = 0;
                    std::vector<Wall> walls = { };
                    std::unordered_map<std::string, std::string> properties;

                    inline const std::vector<Wall> &getWalls() const { return walls; };
                };

            protected:
                std::vector<Room> rooms;
                static std::vector<Room> load(const json& j);

            public:
                explicit Map(const json& j);

                ~Map() = default;
                Map(const Map &) = delete;
                Map &operator=(const Map &) = delete;

                inline const std::vector<Room> &getRooms() const { return rooms; }
        };

        void from_json(const json &j, Map::Wall &w);
        void from_json(const json &j, Map::Room &r);
    }
}

#endif //BMSTU_MAP_CORE_MODEL_MAP_HPP
