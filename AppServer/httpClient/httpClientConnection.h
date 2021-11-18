//
// Created by UlianaBespalova on 10.11.2021.
//
#ifndef HTTPCLIENT_HTTPCLIENTCONNECTION_H
#define HTTPCLIENT_HTTPCLIENTCONNECTION_H

#include "baseConnection.h"
#include "types.h"

class HttpClientConnection : public BaseConnection {
public:
    HttpClientConnection(ip::tcp::socket socket, mapType) :
            BaseConnection(std::move(socket)) {}

    bool isStart() override {}
    void start() override {}
    void stop() override {}

protected:
    void doRead() override {}
    void onRead() override {}
    void doWrite() override {}
    void onWrite() override {}

    std::string *pResponse;
    boost::asio::streambuf reqBuffer;
    boost::asio::streambuf resBuffer;
};

void helloConn();

#endif //HTTPCLIENT_HTTPCLIENTCONNECTION_H
