#include "core/core.hpp"
#include "network/httpClient.h"
#include "ui/mainWindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    HttpClient client;
    ResponseStruct resultStruct;

    struct { const char *address; unsigned short int port; const char *target; } servers[] = {
            { "152.70.54.11", 8000, "/data" },
    };

    bool got_data = false;
    for (auto server : servers) {
        Response result = client.makeGetRequest(server.address, server.port, server.target);
        resultStruct = HttpClient::parseResponse(result);
        printf("status %u\n", resultStruct.status);
        if (resultStruct.status == 200) {
            got_data = true;
            break;
        }
    }
    if (not got_data) return -1;

    Core::Model::Map m(Core::json::parse(resultStruct.body));

    QApplication a(argc, argv);
    MainWindow w(&m);
    w.resize(800, 600);
    w.show();

    return a.exec();
}