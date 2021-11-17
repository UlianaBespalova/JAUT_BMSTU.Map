#include "gtest/gtest.h"

#include "core.hpp"

using namespace Core;

namespace ModelTesting {
    TEST(MapModel, load)
    {
        json j = {
                { "rooms", {
                        {
                                { "type", 1 },
                                { "walls", {
                                        {{ "start", { 1, 2 }}, { "end", { 3, 4 }}},
                                }
                                }
                        }
                },
                }
        };
        EXPECT_NO_FATAL_FAILURE(Model::Map model(j));
    }

    TEST(MapModel, parse_empty)
    {
        auto j = R"({})"_json;
        EXPECT_NO_FATAL_FAILURE(Model::Map model(j));
    }

    TEST(MapModel, parse_full)
    {
        auto j = R"(
    {
      "floors": [
        {
          "floor": 5,
          "rooms": [
            {
              "type": 2,
              "walls": [
                { "start": [100, 100], "end": [100, 250] },
                { "start": [100, 250], "end": [700, 250] },
                { "start": [700, 250], "end": [700, 100] },
                { "start": [700, 100], "end": [100, 100] }
              ],
              "properties": {
                "description": "Main hallway"
              }
            },
            {
              "type": 1,
              "walls": [
                { "start": [100, 250], "end": [100, 350] },
                { "start": [100, 350], "end": [200, 350] },
                { "start": [200, 350], "end": [200, 250] },
                { "start": [200, 250], "end": [175, 250] },
                { "start": [175, 250], "end": [125, 250], "type": 2 },
                { "start": [125, 250], "end": [100, 250] }
              ],
              "properties": {
                "description": "W/C",
                "gender": "F"
              }
            }
          ]
        }
      ]
    }
    )"_json;
        Model::Map model(j);

        EXPECT_EQ(model.getRooms().size(), 2);

        Model::Room hallway = model.getRooms()[0];
        EXPECT_EQ(hallway.floor, 5);
        EXPECT_EQ(hallway.type, Model::Room::Type::Corridor);
        EXPECT_NE(hallway.properties.find("description"), hallway.properties.end());
        EXPECT_EQ(hallway.properties["description"], "Main hallway");

        Model::Room bathroom = model.getRooms()[1];
        EXPECT_EQ(bathroom.floor, 5);
        EXPECT_EQ(bathroom.type, Model::Room::Type::Cabinet);
        EXPECT_NE(bathroom.properties.find("description"), hallway.properties.end());
        EXPECT_EQ(bathroom.properties["description"], "W/C");
        EXPECT_NE(bathroom.properties.find("gender"), hallway.properties.end());
        EXPECT_EQ(bathroom.properties["gender"], "F");
    }

    TEST(MapModel, remote_load)
    {
        Network::NetManager net("http://152.70.54.11:8000");
        json j = net.map_request();
        Model::Map model(j);
        EXPECT_GT(model.getRooms().size(), 0);
    }
}

namespace ViewTesting {
    class DummyCanvas {
        public:
            struct Line { Geometry::Point start, end; };

            std::vector<Line> _lines;
            View::Color _color;

        public:
            DummyCanvas() : _color({ 0, 0, 0 }), _lines() { }
            inline void drawLine(Line line) { _lines.push_back(line); }
            inline void setColor(View::Color color) { _color = color; }
    };

    class DummyDrawer : public View::IDrawer {
        public:
            DummyCanvas *canvas;

            explicit DummyDrawer(DummyCanvas &_canvas) : View::IDrawer(), canvas(&_canvas) { }

            void drawLine(Geometry::Point start, Geometry::Point end) override {
                canvas->drawLine({ start, end });
            };

            void setColor(View::Color color) override {  canvas->setColor(color); };
    };

    TEST(MapView, drawing)
    {
        auto j = R"(
{
  "rooms": [
    { "type": 2, "walls": [
        { "start": [100, 100], "end": [100, 250] },
        { "start": [100, 250], "end": [700, 250] },
        { "start": [700, 250], "end": [700, 100] },
        { "start": [700, 100], "end": [100, 100] }
      ]
    },
    { "type": 1, "walls": [
        { "start": [100, 250], "end": [100, 350] },
        { "start": [100, 350], "end": [200, 350] },
        { "start": [200, 350], "end": [200, 250] },
        { "start": [200, 250], "end": [175, 250] },
        { "start": [175, 250], "end": [125, 250], "type": 2 },
        { "start": [125, 250], "end": [100, 250] }
      ]
    }
  ]
}
)"_json;
        Model::Map model(j);

        DummyCanvas canvas;
        DummyDrawer drawer(canvas);
        View::Map view(&model, &drawer);
        view.drawMap();

        EXPECT_EQ(canvas._color.r, 0);
        EXPECT_EQ(canvas._color.g, 0);
        EXPECT_EQ(canvas._color.b, 0);

        EXPECT_EQ(canvas._lines.size(), 10);
    }
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}