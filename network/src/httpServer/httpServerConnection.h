//
// Created by UlianaBespalova on 10.11.2021.
//
#ifndef HTTPSERVERCONNECTION_H
#define HTTPSERVERCONNECTION_H

#include <boost/asio.hpp>
#include <boost/beast.hpp>

#include "baseConnection.h"
#include "router.h"
#include "types.h"

using namespace boost::beast;

class HttpServerConnection : public BaseConnection {
public:
    HttpServerConnection(boost::asio::ip::tcp::socket socket, Router *router) :
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

    flat_buffer buffer{1024};
    Request request;
    Response response;
    Router *router;
};

void helloServerConn();

#endif //HTTPSERVERCONNECTION_H
