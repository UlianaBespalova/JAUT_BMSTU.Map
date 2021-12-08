#include <iostream>
#include <fstream>

#include "core/core.hpp"


using namespace Core;

class DummyDrawer : public View::IDrawer {
    public:
        void drawLine(Geometry::Point start, Geometry::Point end) override {
            printf("Drawing a line from [%.2f; %.2f] to [%.2f; %.2f]\n", start.x, start.y, end.x, end.y);
        }

        void setColor(View::Color color) override {
            printf("Setting a color to #%02X%02X%02X\n", color.r, color.g, color.b);
        }
};

int main(int argc, char *argv[])
{
    printf("Creating Model::Map... ");
    Model::Map model(json::parse(R"({"floors":[{"floor":8,"rooms":[{"type":2,"walls":[{"start":[557,510],"end":[557,733]},{"start":[2981,510],"end":[557,510]},{"start":[2981,733],"end":[2981,510]},{"start":[557,733],"end":[2981,733]}]}]}]})"));
    printf("Done: %lu rooms\n", model.getRooms().size());


    printf("Creating Drawer... ");
    DummyDrawer drawer;
    printf("Done\nCreating View::Map... ");
    View::Map view(&model, &drawer);
    printf("Done\nDrawing map:\n");

    view.drawMap();

    return 0;
}