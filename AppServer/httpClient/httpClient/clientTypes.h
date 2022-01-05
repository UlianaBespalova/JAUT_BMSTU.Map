//
// Created by UlianaBespalova on 11.11.2021.
//

#ifndef TYPES_H
#define TYPES_H

#include <boost/beast.hpp>

using beast = boost::beast;

typedef http::response<http::dynamic_body> Response;
typedef http::request<http::string_body> Request;
typedef http::request<http::dynamic_body> PostRequest;

typedef std::map<std::string, std::string> Params;

struct ResponseStruct {
    unsigned int status;
    std::string body;
};

struct HostAddress {
    std::string domain;
    std::string ip;
    unsigned short port;
    HostAddress(std::string domain, std::string ip, unsigned short port)
            : domain(std::move(domain)), ip(ip), port(port) {}
};

#endif  // TYPES_H
