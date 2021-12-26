//
// Created by UlianaBespalova on 10.11.2021.
//
#include <iostream>

#include "httpServer.h"

#include "boost/property_tree/json_parser.hpp"
#include "boost/property_tree/ptree.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    std::cout << "httpServer is running" << std::endl;

    std::string address = "127.0.0.1";
    int port = 8000;
    auto* server = new HttpServer(address, port);
    server->run();

    delete server;
    return 0;
}

