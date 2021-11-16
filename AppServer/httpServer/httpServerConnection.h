//
// Created by UlianaBespalova on 10.11.2021.
//
#ifndef HTTPSERVERCONNECTION_H
#define HTTPSERVERCONNECTION_H

#include <boost/asio.hpp>

#include "baseConnection.h"
#include "router.h"

using namespace boost::asio;

class HttpServerConnection : public BaseConnection {
public:
    HttpServerConnection(ip::tcp::socket socket, Router *router) :
    BaseConnection(std::move(socket)), router(router) {}
    virtual ~HttpServerConnection() = default;

    bool isStart() override {}
    void start() override {}
    void stop() override {}

protected:
    void doRead() override {}
    void onRead() override {}
    void doWrite() override {}
    void onWrite() override {}

    Router *router;
};

void helloServerConn();

#endif //HTTPSERVERCONNECTION_H
