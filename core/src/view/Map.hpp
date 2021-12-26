#ifndef BMSTU_MAP_CORE_VIEW_MAP_HPP
#define BMSTU_MAP_CORE_VIEW_MAP_HPP

#include "../model/Map.hpp"

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
                Map(Model::Map *_model, IDrawer *_drawer) : model(_model), drawer(_drawer) { }
                ~Map() = default;
                Map(const Map &) = delete;
                Map &operator=(const Map &) = delete;

                void drawMap();

            protected:
                Model::Map *model;
                IDrawer *drawer;

                void drawRoom(const Model::Map::Room &room);

                void drawWall(const Model::Map::Wall &wall);
        };
    }
}

#endif //BMSTU_MAP_CORE_VIEW_MAP_HPP
