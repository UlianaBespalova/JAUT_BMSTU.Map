//
// Created by UlianaBespalova on 10.11.2021.
//
#ifndef HTTPSERVER_H
#define HTTPSERVER_H

#include <boost/asio.hpp>

using namespace boost::asio;

class HttpServer {
public:
    HttpServer(ip::address &address, unsigned short port) {}

    void run() {}

protected:
    void accept() {}

    io_service ioContext;
    ip::tcp::endpoint *endpoint = nullptr;
    ip::tcp::acceptor *acceptor = nullptr;
    ip::tcp::socket *socket = nullptr;
};

void helloServer();

#endif //HTTPSERVER_H
