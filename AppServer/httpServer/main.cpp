//
// Created by UlianaBespalova on 10.11.2021.
//
#include <iostream>
#include <memory>

#include "httpServer.h"

int main() {
    std::cout << "httpServer is running" << std::endl;

    std::string address = "127.0.0.1";
    int port = 8000;
    HttpServer server {address, port};
    server.run();

    return 0;
}

