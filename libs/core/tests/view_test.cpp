#include "gtest/gtest.h"

#include "core/core.hpp"


using namespace Core;

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