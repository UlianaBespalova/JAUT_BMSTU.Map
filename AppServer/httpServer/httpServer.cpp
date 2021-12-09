//
// Created by UlianaBespalova on 10.11.2021.
//
#include <iostream>
#include <boost/make_shared.hpp>

#include "httpServer.h"
#include "httpServerConnection.h"


HttpServer::HttpServer(std::string& address, int port) :
    acceptor(context, endpoint),
    socket(context) {

    std::cout << "HttpServer" << std::endl;

    auto m_address = ip::make_address(address);
    auto m_port = static_cast<unsigned short>(port);

    endpoint = ip::tcp::endpoint(m_address, m_port);
    acceptor = ip::tcp::acceptor(context, endpoint);

    std::cout << endpoint.address() << " " << endpoint.port() << std::endl;
    boost::system::error_code err;
    acceptor.set_option(socket_base::reuse_address(true), err);
    if (err) {
        std::cerr << "err:" << err.message() << std::endl;
    }
    acceptor.listen(socket_base::max_listen_connections, err);
    if (err) {
        std::cerr << "err:" << err.message() << std::endl;
    }
}

void HttpServer::accept() {
    acceptor.async_accept(socket, [&](boost::beast::error_code err) {
        std::cout << "Accept" << std::endl;
        if (err) {
            std::cout << "Err" << std::endl;
        }
        if (!err) {
            std::cout << "New connection" << std::endl;
            boost::make_shared<HttpServerConnection>(std::move(socket), &router)->start();
        }
        accept();
    });
}

void HttpServer::run() {
    std::cout << "Run" << std::endl;
    accept();
    context.run();
}





