//
// Created by UlianaBespalova on 10.11.2021.
//
#ifndef BASECONNECTION_H
#define BASECONNECTION_H

#include "boost/enable_shared_from_this.hpp"
#include <boost/asio.hpp>

using namespace boost::asio;

class BaseConnection : boost::enable_shared_from_this<BaseConnection>, boost::noncopyable {
public:
    BaseConnection(ip::tcp::socket socket) : socket(std::move(socket)) {}
    virtual ~BaseConnection() = default;

    virtual bool isStart() = 0;
    virtual void start() = 0;
    virtual void stop() = 0;

protected:
    virtual void doRead() = 0;
    virtual void onRead() = 0;
    virtual void doWrite() = 0;
    virtual void onWrite() = 0;

    ip::tcp::socket socket;
};

#endif //BASECONNECTION_H
