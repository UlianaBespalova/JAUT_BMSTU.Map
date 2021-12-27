#include "core/core.hpp"
#include "network/httpClient.h"
#include "ui/mainWindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    struct { HostAddress host; std::string target; } servers[] = {
            {{ "", "152.70.54.11", 8000 }, "/data" },
    };

    HttpClient client;

    struct { bool success = false; ResponseStruct result; } search;
    for (const auto &server : servers) {
        Response response = client.makeGetRequest(server.host, server.target);
        search.result = client.parseResponse(response);

        if (search.result.status == 200) {
            search.success = true;
            break;
        }
    }
    if (not search.success) return -1;

    Core::Model::Map m(Core::json::parse(search.result.body));

    QApplication a(argc, argv);
    MainWindow w(&m);
    w.resize(800, 600);
    w.show();

    return a.exec();
}