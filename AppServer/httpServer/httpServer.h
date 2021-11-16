//
// Created by UlianaBespalova on 10.11.2021.
//
#ifndef HTTPSERVER_H
#define HTTPSERVER_H

#include <boost/asio.hpp>
#include "baseServer.h"

using namespace boost::asio;

class HttpServer : public BaseServer {
public:
    HttpServer(ip::address address, unsigned short port) {}

    void run() override {}

protected:
    void accept() override {}

    io_service ioContext;
};

void helloServer();

#endif //HTTPSERVER_H
