//
// Created by UlianaBespalova on 10.11.2021.
//
#include <boost/lexical_cast.hpp>
#include <boost/system/error_code.hpp>
#include <iostream>
#include <utility>

#include "httpClient.h"


std::string getToken() {
    return "bb-at-1rrz8bvnkc5xb7lsx3ga4wpscn73qkfzc5h6ftr32s134";
}




HttpClient::HttpClient() : socket(context), resolver(context) { }

bool HttpClient::connect(unsigned short port = 80) {
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



HttpsClient::HttpsClient() : ctx(asio::ssl::context::method::sslv23_client), ssock(svc, ctx) { }

bool HttpsClient::connect(unsigned short port = 443) {
    try {
        ssock.lowest_layer().connect({ {asio::ip::address::from_string(HttpsClient::address_ip)}, port });
        ssock.handshake(asio::ssl::stream_base::handshake_type::client);
        return true;
    } catch (const boost::exception_detail::clone_impl<boost::exception_detail::
    error_info_injector<boost::system::system_error> > &error) {
        std::cout << error.what() << std::endl;
        return false;
    }
}

void HttpsClient::requestGet(const std::string& target) {
    const int version = 11;
    Request request{beast::http::verb::get, target, version};
    request.set(beast::http::field::host, HttpsClient::address_domen);
    request.set(beast::http::field::user_agent, BOOST_BEAST_VERSION_STRING);
    request.set("x-bb-token", getToken() );

    std::cout<<"request: \n" << request << std::endl;

    beast::http::write(ssock, request);
}

Response HttpsClient::getResponse() {
    std::cout << "4. ok" << std::endl;
    Response result;
    beast::http::read(ssock, buffer, result);
    boost::system::error_code ec;

    ssock.lowest_layer().close();
    svc.stop();
    return result;
}

Response HttpsClient::makeGetRequest(std::string _address_domen, std::string _address_ip, unsigned short port, const std::string& target,
                                     Params* params, std::string header) {
    HttpsClient::address_domen = std::move(_address_domen);
    HttpsClient::address_ip = std::move(_address_ip);

    bool connected = connect(port);
    if (!connected) {
        return {};
    }
    if (params == nullptr || (*params).empty()) {
        HttpsClient::requestGet(target);
    } else {
        auto url = getUrl(target, params);
        HttpsClient::requestGet(url);
    }
    return getResponse();
}

void HttpsClient::requestPost(const std::string& target) {

    std::string body = "  {\"parent_uuid\":\"\",\"query\":\"\",\"type\":\"group\"}  ";

    const int version = 11;
    Request request{beast::http::verb::post, target, version};
    request.set(beast::http::field::host, HttpsClient::address_domen);
    request.set(beast::http::field::user_agent, BOOST_BEAST_VERSION_STRING);
    request.set(boost::beast::http::field::content_type, "application/json");

    request.set("x-bb-token", getToken() );
    request.set(http::field::content_length, body.length()); //??
    request.set(http::field::body, body);

    request.prepare_payload();
    std::cout<<request << body.length() <<std::endl;
    beast::http::write(ssock, request);
}

Response HttpsClient::makePostRequest(std::string _address_domen, std::string _address_ip,
                                      unsigned short port, const std::string& target,
                                      Params* params, std::string header) {
    HttpsClient::address_domen = std::move(_address_domen);
    HttpsClient::address_ip = std::move(_address_ip);
    bool connected = connect(port);
    if (!connected) {
        return {};
    }
    HttpsClient::requestPost(target);
    return getResponse();
}
