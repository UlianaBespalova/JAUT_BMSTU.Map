//
// Created by UlianaBespalova on 10.11.2021.
//
#ifndef HTTPCLIENT_H
#define HTTPCLIENT_H

#include <boost/asio.hpp>

#include "types.h"

using namespace boost::asio;

class HttpClient {
public:
    HttpClient(std::string &address, unsigned short port) {}
    void request(mapType data) {}
    Response getResponse() {}

protected:
    void connect(mapType request) {}

    io_context ioContext;
    ip::tcp::endpoint endpoint;
};

void helloClient();

#endif //HTTPCLIENT_H
