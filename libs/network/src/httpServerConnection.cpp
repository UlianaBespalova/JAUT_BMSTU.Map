//
// Created by UlianaBespalova on 10.11.2021.
//
#include <iostream>

#include "httpServerConnection.h"

HttpServerConnection::HttpServerConnection(ip::tcp::socket socket, Router *router) : socket(std::move(socket)),
                                                                                     router(router) {}

void HttpServerConnection::start() {
    std::cout << "start OK" << std::endl;
    doRead();
}

void HttpServerConnection::doRead() {
    auto self = shared_from_this();
    http::async_read(socket, buffer, request, [self](error_code err, size_t bytes_transfered) {
        if(!err) {
            self->onRead();
        }
    });
}

void HttpServerConnection::onRead() {
    response = router->execute(request);
    std::cout << response << std::endl;
    doWrite();
}

void HttpServerConnection::doWrite() {
    auto self = shared_from_this();
    boost::beast::http::async_write(socket, response, [self](boost::beast::error_code err, size_t bytes_transfered) {
        if (!err) {
            self->socket.shutdown(ip::tcp::socket::shutdown_send, err);
            self->socket.close();
        }
    });
}

void HttpServerConnection::onWrite() {}
