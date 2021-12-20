#ifndef BMSTU_MAP_CORE_VIEW_MAP_HPP
#define BMSTU_MAP_CORE_VIEW_MAP_HPP

#include "ModelMap.hpp"

namespace Core {
    namespace View {
        struct Color {
            byte_t r, g, b;
        };

        class IDrawer {
            public:
                virtual void drawLine(Geometry::Point start, Geometry::Point end) = 0;
                virtual void setColor(Color) = 0;
        };

        class Map {
            public:
                typedef std::vector<Geometry::Point> Path;

                Map(Model::Map *_model, IDrawer *_drawer);
                ~Map() = default;
                Map(const Map &) = delete;
                Map &operator=(const Map &) = delete;

                void drawMap();
                void setPath(const Path &path);

            protected:
                Model::Map *model;
                IDrawer *drawer;

                Path path;
                bool hasPath = false;

                void drawPath(const Path &room);
                void drawRoom(const Model::Map::Room &room);
                void drawWall(const Model::Map::Wall &wall);
        };
    }
}

#endif //BMSTU_MAP_CORE_VIEW_MAP_HPP
