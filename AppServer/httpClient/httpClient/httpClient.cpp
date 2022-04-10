//
// Created by UlianaBespalova on 10.11.2021.
//
#include <iostream>
#include <utility>

#include "httpClient.h"

HttpClient::HttpClient() : socket(context), resolver(context) { }

bool HttpClient::connect(unsigned short port = 443) {
    auto const results = resolver
            .resolve(HttpClient::address, std::to_string(port));
    try {
        asio::connect(socket, results.begin(), results.end());
        return true;
    } catch (const boost::exception_detail::clone_impl<boost::exception_detail::
    error_info_injector<boost::system::system_error> > &error) {
        std::cout << error.what() << std::endl;
        return false;
    }
}

void HttpClient::requestGet(const std::string& target) {
    const int version = 11;
    Request request{beast::http::verb::get, target, version};
    request.set(beast::http::field::host, HttpClient::address);
    request.set(beast::http::field::user_agent, BOOST_BEAST_VERSION_STRING);
    beast::http::write(socket, request);
}

Response HttpClient::getResponse() {
    Response result;
    beast::http::read(socket, buffer, result);
    boost::system::error_code ec;
    socket.shutdown(asio::ip::tcp::socket::shutdown_both, ec);
    if(ec && ec != boost::system::errc::not_connected)
        std::cout << "Connection error" << std::endl;
    return result;
}

std::string getUrl(const std::string &target, Params* params) {
    if (params== nullptr) return target;
    std::string url = target+"?";
    auto iter = (*params).begin();
    for (; iter != (*params).end(); iter++) {
        url += iter->first + "=" + iter->second + "&";
    }
    url.pop_back();
    return url;
}

Response HttpClient::makeGetRequest(std::string _address, unsigned short port, const std::string& target,
                                          Params* params, std::string header) {
    HttpClient::address = std::move(_address);
    bool connected = connect(port);
    if (!connected) {
        return {};
    }
    if (params == nullptr || (*params).empty()) {
        HttpClient::requestGet(target);
    } else {
        auto url = getUrl(target, params);
        HttpClient::requestGet(url);
    }
    return getResponse();
}

ResponseStruct HttpClient::parseResponse(Response response) {
    ResponseStruct res = ResponseStruct();
    res.status = response.result_int();
    std::string str;
    for (auto seq : response.body().data()) {
        auto* cbuf = boost::asio::buffer_cast<const char*>(seq);
        str.append(cbuf, boost::asio::buffer_size(seq));
    }
    res.body = str;
    return res;
}