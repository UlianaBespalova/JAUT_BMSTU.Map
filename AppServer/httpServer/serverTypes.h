//
// Created by UlianaBespalova on 11.11.2021.
//
#ifndef SERVERTYPES_H
#define SERVERTYPES_H
#include <boost/beast.hpp>

using namespace boost::beast;

typedef http::response<http::string_body> ResponseString;
typedef http::request<http::string_body> Request;
typedef std::map<std::string, std::string> mapType;


#endif //SERVERTYPES_H
