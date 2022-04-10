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

                void drawMap()
                {
                    assert(drawer != nullptr);
                    assert(model != nullptr);

                    for (const auto &room: model->getRooms()) {
                        drawRoom(room);
                    }
                }

            protected:
                Model::Map *model;
                IDrawer *drawer;

                void drawRoom(const Model::Room &room)
                {
                    switch (room.type) {
                        case Model::Room::Type::Unknown:drawer->setColor({ 255, 0, 0 });
                            break;
                        case Model::Room::Type::Cabinet:drawer->setColor({ 0, 0, 0 });
                            break;
                        case Model::Room::Type::Corridor:drawer->setColor({ 255, 0, 0 });
                            break;
                        case Model::Room::Type::Stairs:drawer->setColor({ 127, 255, 127 });
                            break;
                        case Model::Room::Type::Elevator:drawer->setColor({ 0, 255, 0 });
                            break;
                        default:
#ifndef NDEBUG
                            throw std::runtime_error("Unknown _color!");
#endif
                            break;
                    }

                    for (const auto &wall: model->getWalls(room)) {
                        drawWall(wall);
                    }
                }

                void drawWall(const Model::Wall &wall)
                {
                    drawer->drawLine(wall.start, wall.end);
                }
        };
    }
}

#endif //BMSTU_MAP_CORE_VIEW_MAP_HPP
