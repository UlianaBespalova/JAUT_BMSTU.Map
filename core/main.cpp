#include <iostream>
#include <fstream>

#include "core.hpp"


using namespace Core;

class DummyDrawer : public View::IDrawer {
    public:
        void drawLine(Geometry::Point start, Geometry::Point end) override {
            printf("Drawing a line from [%f; %f] to [%f; %f]\n", start.x, start.y, end.x, end.y);
        }

        void setColor(View::Color color) override {
            printf("Setting a color to #%02X%02X%02X\n", color.r, color.g, color.b);
        }
};

int main(int argc, char *argv[])
{
    const std::string FILENAME = "../test_data.json";

    std::ifstream i(FILENAME);
    if (not i.is_open()) {
        printf("Could not open file '%s'!", FILENAME.c_str());
        return -1;
    }

    json loaded_data;
    printf("Loading data from '%s'... ", FILENAME.c_str());
    i >> loaded_data;
    printf("Done\n");

    printf("Creating Model::Map... ");
    Model::Map model(loaded_data);
    printf("Done\n");

    printf("Creating Drawer... ");
    DummyDrawer drawer;
    printf("Done\nCreating View::Map... ");
    View::Map view(&model, &drawer);
    printf("Done\nDrawing map:\n");

    view.drawMap();

    return 0;
}