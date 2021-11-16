//
// Created by UlianaBespalova on 10.11.2021.
//
#ifndef HTTPCLIENT_HTTPCLIENTCONNECTION_H
#define HTTPCLIENT_HTTPCLIENTCONNECTION_H

#include "baseConnection.h"

class HttpClientConnection : public BaseConnection {
public:
    HttpClientConnection(ip::tcp::socket socket, std::map<std::string, std::string>) :
            BaseConnection(std::move(socket)) {}

    bool isStart() override {}
    void start() override {}
    void stop() override {}

protected:
    void doRead() override {}
    void onRead() override {}
    void doWrite() override {}
    void onWrite() override {}
};

void helloConn();

#endif //HTTPCLIENT_HTTPCLIENTCONNECTION_H
