//
// Created by UlianaBespalova on 10.11.2021.
//

#include <boost/lexical_cast.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/system/error_code.hpp>
#include <iostream>
#include <utility>

#include "httpClient.h"

using boostSystemErr = boost::system::system_error;
using exception = boost::exception_detail;
using ptree = boost::property_tree;

Response BaseClient::getConnection(unsigned short port,
                                   const std::string& target, Params* params,
                                   Params* headers) {
    bool connected = connect(port);
    if (!connected) {
        return {};
    }
    std::string url = target;
    if (params && !params->empty()) {
        url = getUrl(target, params);
    }
    requestGet(url, headers);
    return getResponse();
}

std::string BaseClient::getUrl(const std::string& target, Params* params) {
    if (!params) return target;
    std::string url = target + "?";
    auto iter = params->begin();
    for (; iter != params->end(); iter++) {
        url += iter->first + "=" + iter->second + "&";
    }
    url.pop_back();
    return url;
}

ResponseStruct BaseClient::parseResponse(Response response) {
    ResponseStruct res = ResponseStruct();
    res.status = response.result_int();
    std::string str;
    for (auto seq : response.body().data()) {
        auto* cbuf = asio::buffer_cast<const char*>(seq);
        str.append(cbuf, asio::buffer_size(seq));
    }
    res.body = str;
    return res;
}

HttpClient::HttpClient() : socket(context), resolver(context) {}

bool HttpClient::connect(unsigned short port = 80) {
    auto const results =
            resolver.resolve(HttpClient::address_ip, std::to_string(port));
    try {
        asio::connect(socket, results.begin(), results.end());
        return true;
    } catch (const exception::clone_impl<
            exception::error_info_injector<boostSystemErr> >& error) {
        std::cout << error.what() << std::endl;
        return false;
    }
}

void HttpClient::requestGet(const std::string& target, Params* headers) {
    const int version = 11;
    Request request{beast::http::verb::get, target, version};
    request.set(beast::http::field::host, HttpClient::address_ip);
    request.set(beast::http::field::user_agent, BOOST_BEAST_VERSION_STRING);

    if (headers && !headers->empty()) {
        auto iter = headers->begin();
        for (; iter != headers->end(); iter++) {
            request.set(iter->first, iter->second);
        }
    }
    beast::http::write(socket, request);
}

Response HttpClient::getResponse() {
    Response result;
    beast::http::read(socket, buffer, result);
    boost::system::error_code ec;
    socket.shutdown(asio::ip::tcp::socket::shutdown_both, ec);
    if (ec && ec != boost::system::errc::not_connected)
        std::cout << "Connection error" << std::endl;
    return result;
}

Response HttpClient::makeGetRequest(const HostAddress& host,
                                    const std::string& target, Params* params,
                                    Params* headers) {
    HttpClient::address_ip = std::move(host.ip);
    return getConnection(host.port, target, params, headers);
}

HttpsClient::HttpsClient()
        : ctx(asio::ssl::context::method::sslv23_client), socket(svc, ctx) {}

bool HttpsClient::connect(unsigned short port = 443) {
    try {
        socket.lowest_layer().connect(
                {{asio::ip::address::from_string(HttpsClient::address_ip)}, port});
        socket.handshake(asio::ssl::stream_base::handshake_type::client);
        return true;
    } catch (const exception::clone_impl<
            exception::error_info_injector<boostSystemErr> >& error) {
        std::cout << error.what() << std::endl;
        return false;
    }
}

void HttpsClient::requestGet(const std::string& target, Params* headers) {
    const int version = 11;
    Request request{beast::http::verb::get, target, version};
    request.set(beast::http::field::host, HttpsClient::address_domain);
    request.set(beast::http::field::user_agent, BOOST_BEAST_VERSION_STRING);

    if (headers && !headers->empty()) {
        auto iter = headers->begin();
        for (; iter != headers->end(); iter++) {
            request.set(iter->first, iter->second);
        }
    }
    beast::http::write(socket, request);
}

Response HttpsClient::getResponse() {
    Response result;
    beast::http::read(socket, buffer, result);
    boost::system::error_code ec;
    socket.lowest_layer().close();
    svc.stop();
    return result;
}

Response HttpsClient::makeGetRequest(const HostAddress& host,
                                     const std::string& target, Params* params,
                                     Params* headers) {
    HttpsClient::address_domain = std::move(host.domain);
    HttpsClient::address_ip = std::move(host.ip);

    return getConnection(host.port, target, params, headers);
}

void HttpsClient::requestPost(const std::string& target, Params* headers,
                              Params* body) {
    ptree::ptree root;
    if (body && !body->empty()) {
        auto iter = body->begin();
        for (; iter != body->end(); iter++) {
            root.put(iter->first, iter->second);
        }
    }
    std::ostringstream buf;
    write_json(buf, root, false);
    std::string json = buf.str();

    asio::streambuf request;
    std::ostream request_stream(&request);
    request_stream << "POST " << target << " HTTP/1.1 \r\n";
    request_stream << "Host:" << HttpsClient::address_domain << "\r\n";
    request_stream << "User-Agent: " << BOOST_BEAST_VERSION_STRING << "\r\n";
    request_stream << "Content-Type: application/json; charset=utf-8 \r\n";
    request_stream << "Accept: */*\r\n";
    request_stream << "Content-Length: " << json.length() << "\r\n";
    if (headers && !headers->empty()) {
        auto iter = headers->begin();
        for (; iter != headers->end(); iter++) {
            request_stream << iter->first << ": " << iter->second << "\r\n";
        }
    }
    request_stream << "Connection: close\r\n\r\n";
    request_stream << json;

    asio::write(socket, request);
}

Response HttpsClient::makePostRequest(const HostAddress& host,
                                      const std::string& target, Params* params,
                                      Params* headers, Params* body) {
    HttpsClient::address_domain = std::move(host.domain);
    HttpsClient::address_ip = std::move(host.ip);
    bool connected = HttpsClient::connect(host.port);
    if (!connected) {
        return {};
    }
    HttpsClient::requestPost(target, headers, body);
    return HttpsClient::getResponse();
}
