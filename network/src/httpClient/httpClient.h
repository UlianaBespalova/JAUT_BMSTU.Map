//
// Created by UlianaBespalova on 10.11.2021.
//
#ifndef HTTPCLIENT_H
#define HTTPCLIENT_H

#include <boost/asio.hpp>

#include "baseClasses/types.h"

namespace asio = boost::asio;
namespace beast = boost::beast;

class HttpClient {
public:
    HttpClient();

    Response makeGetRequest(std::string _address, unsigned short port, const std::string& target,
                                  Params* params = nullptr, std::string header = "");
    static ResponseStruct parseResponse(Response response);
protected:
    bool connect(unsigned short port);
    void requestGet(const std::string& target);
    Response getResponse();

    asio::io_context context;
    asio::ip::tcp::resolver resolver;
    asio::ip::tcp::socket socket;

    std::string address;
    beast::flat_buffer buffer;
};

#endif //HTTPCLIENT_H
