#ifndef BMSTU_MAP_CORE_MODEL_MAP_HPP
#define BMSTU_MAP_CORE_MODEL_MAP_HPP

#include <vector>
#include <string>
#include "geometry.hpp"
#include "graph.h"


namespace Core {
    namespace Model {
        class Map {
            public:
                struct Wall {
                    enum class Type { Solid, Pass, Door } type = Type::Solid;
                    Geometry::Point start = { }, end = { };
                };

                typedef unsigned int id_t;

                struct Room {
                    id_t id;
                    enum class Type { Unknown, Cabinet, Corridor, Stairs, Elevator } type = Type::Unknown;
                    int floor = 0;
                    std::vector<Wall> walls = { };
                    std::unordered_map<std::string, std::string> properties;

                    inline const std::vector<Wall> &getWalls() const { return walls; };
                };

            protected:
                typedef std::unordered_map<id_t, Room> rooms_t;
                rooms_t rooms;

            public:
                explicit Map(const json& j);

                ~Map() = default;
                Map(const Map &) = delete;
                Map &operator=(const Map &) = delete;

                inline const rooms_t &getRooms() const { return rooms; }
                Graph graph;
//                inline const Graph &getGraph() const { return graph; }
        };

        void from_json(const json &j, Map::Wall &w);
        void from_json(const json &j, Map::Room &r);
    }
}

#endif //BMSTU_MAP_CORE_MODEL_MAP_HPP
