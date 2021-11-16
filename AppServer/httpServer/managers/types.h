//
// Created by UlianaBespalova on 11.11.2021.
//
#ifndef TYPES_H
#define TYPES_H
#include <boost/beast.hpp>
//#include <boost/beast.hpp>

using namespace boost::beast;

typedef http::response<http::string_body> responseType;
typedef http::request<http::string_body> requestType;
typedef std::map<std::string, std::string> mapType;


#endif //TYPES_H
