//
// Created by UlianaBespalova on 10.11.2021.
//
#ifndef HTTPCLIENT_H
#define HTTPCLIENT_H

#include <boost/asio.hpp>
#include "baseClient.h"

using namespace boost::asio;

class HttpClient : public BaseClient {
public:
    HttpClient(ip::address address, unsigned short port) {}
    void request(std::map<std::string, std::string> data) override{}

protected:
    void connect(std::map<std::string, std::string> request) override {}

    io_context ioContext;
    ip::tcp::endpoint endpoint;
};

void helloClient();

#endif //HTTPCLIENT_H
