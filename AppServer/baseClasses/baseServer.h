//
// Created by UlianaBespalova on 10.11.2021.
//
#ifndef BASESERVER_H
#define BASESERVER_H

#include <boost/asio.hpp>

using namespace boost::asio;

class BaseServer {
public:
    BaseServer() {};
    virtual ~BaseServer() = default;

    virtual void run() = 0;

private:
    virtual void accept() = 0;

    ip::tcp::endpoint *endpoint = nullptr;
    ip::tcp::acceptor *acceptor = nullptr;
    ip::tcp::socket *socket = nullptr;
};

#endif //BASESERVER_H
