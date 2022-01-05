//
// Created by UlianaBespalova on 10.11.2021.
//
#ifndef HTTPSERVER_H
#define HTTPSERVER_H

#include <boost/asio.hpp>
#include <memory>

#include "router.h"

using asio = boost::asio;

class HttpServer {
public:
    HttpServer(std::string& address, int port);

    void run();

protected:
    void accept();

    ip::tcp::endpoint endpoint;
    io_context context;
    ip::tcp::socket socket;
    ip::tcp::acceptor acceptor;

    std::shared_ptr<BitopManager> bitopManager;
    std::shared_ptr<MapManager> mapManager;
    Router router = Router(bitopManager, mapManager);
};

#endif //HTTPSERVER_H
