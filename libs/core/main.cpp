#include <iostream>
#include <fstream>

#include "core/database.h"
#include "core/core.hpp"
#include "core/database.h"


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

    Database json_db(JSON_TABLE_NAME, JSON_TABLE_FORMAT);
    Model::Map model(json::parse(json_db.read_json()));

    printf("Done: %lu rooms\n", model.getRooms().size());


    printf("Creating Drawer... ");
    DummyDrawer drawer;
    printf("Done\nCreating View::Map... ");
    View::Map view(&model, &drawer);
    printf("Done\nDrawing map:\n");

    view.drawMap();

    return 0;
}