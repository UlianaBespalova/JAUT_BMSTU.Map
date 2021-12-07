//
// Created by UlianaBespalova on 11.11.2021.
//
#ifndef TYPES_H
#define TYPES_H
#include <boost/beast.hpp>

using namespace boost::beast;

typedef http::response<http::string_body> Response;
typedef http::request<http::string_body> Request;
typedef std::map<std::string, std::string> mapType;


#endif //TYPES_H
