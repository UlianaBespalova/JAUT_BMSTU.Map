#include <iostream>

#include "httpServer.h"

#include "boost/property_tree/ptree.hpp"
#include "boost/property_tree/json_parser.hpp"


int main(int argc, char* argv[]) {
    std::cout << "httpServer is running" << std::endl;

    std::string address = "127.0.0.1";
    int port = 8000;
    if (argc > 1) {
        port = atoi(argv[1]);
    }
    auto *server = new HttpServer(address, port);
    server->run();
    delete server;
    return 0;
}
