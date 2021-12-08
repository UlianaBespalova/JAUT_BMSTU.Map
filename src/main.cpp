#include "core/core.hpp"
#include "network/httpClient.h"
#include "BMSTU_Map/mainWindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    Core::Model::Map *m;
    HttpClient *client;

    QApplication a(argc, argv);
    MainWindow w;
    w.resize(800, 600);
    w.show();

    return a.exec();
}