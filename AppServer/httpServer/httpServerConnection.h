//
// Created by UlianaBespalova on 10.11.2021.
//
#ifndef HTTPSERVERCONNECTION_H
#define HTTPSERVERCONNECTION_H

#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/beast.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>

#include "router.h"
#include "serverTypes.h"

using namespace boost::asio;
using namespace boost::beast;

class HttpServerConnection : public boost::enable_shared_from_this<HttpServerConnection>{
public:
    HttpServerConnection(ip::tcp::socket socket, Router* router);
    ~HttpServerConnection() = default;

    void start();

protected:
    void doRead();
    void onRead();
    void doWrite();
    void onWrite();

    flat_buffer buffer{8192};
    Request request;
    ResponseString response;

    ip::tcp::socket socket;
    Router* router;
};

void helloServerConn();

#endif //HTTPSERVERCONNECTION_H
