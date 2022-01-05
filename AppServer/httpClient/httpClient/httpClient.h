//
// Created by UlianaBespalova on 10.11.2021.
//

#ifndef HTTPCLIENT_H
#define HTTPCLIENT_H

#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <utility>

#include "clientTypes.h"

using asio = boost::asio;
using beast = boost::beast;

class BaseClient {
public:
    virtual Response makeGetRequest(const HostAddress& host,
                                    const std::string& target, Params* params,
                                    Params* headers) = 0;

    virtual Response makePostRequest(const HostAddress& host,
                                     const std::string& target, Params* params,
                                     Params* headers, Params* body) = 0;

    ResponseStruct parseResponse(Response response);
    static std::string getUrl(const std::string& target, Params* params);

protected:
    virtual bool connect(unsigned short port) = 0;
    virtual Response getResponse() = 0;
    virtual void requestGet(const std::string& target, Params* headers) = 0;

    Response getConnection(unsigned short port, const std::string& target,
                           Params* params = nullptr, Params* headers = nullptr);

    std::string address_ip;
    beast::flat_buffer buffer;
};

class HttpClient : public BaseClient {
public:
    HttpClient();

    Response makeGetRequest(const HostAddress& host, const std::string& target,
                            Params* params = nullptr,
                            Params* headers = nullptr) override;
    Response makePostRequest(const HostAddress& host, const std::string& target,
                             Params* params = nullptr, Params* headers = nullptr,
                             Params* body = nullptr) override{};

protected:
    bool connect(unsigned short port) override;
    Response getResponse() override;
    void requestGet(const std::string& target,
                    Params* headers = nullptr) override;

    void requestPost(const std::string& target);

    asio::io_context context;
    asio::ip::tcp::resolver resolver;
    asio::ip::tcp::socket socket;
};

class HttpsClient : public BaseClient {
public:
    HttpsClient();

    Response makeGetRequest(const HostAddress& host, const std::string& target,
                            Params* params = nullptr,
                            Params* headers = nullptr) override;
    Response makePostRequest(const HostAddress& host, const std::string& target,
                             Params* params = nullptr, Params* headers = nullptr,
                             Params* body = nullptr) override;

protected:
    bool connect(unsigned short port) override;
    Response getResponse() override;
    void requestGet(const std::string& target,
                    Params* headers = nullptr) override;

    void requestPost(const std::string& target, Params* headers = nullptr,
                     Params* body = nullptr);

    asio::io_service svc;
    asio::ssl::context ctx;
    asio::ssl::stream<asio::ip::tcp::socket> socket;
    std::string address_domain;
};

#endif  // HTTPCLIENT_H
