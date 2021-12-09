//
// Created by UlianaBespalova on 29.11.2021.
//

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

#include "../serverTypes.h"

#ifndef HTTPSERVER_SERIALIZERS_H
#define HTTPSERVER_SERIALIZERS_H


struct FloorReq {
    std::string floor;
    explicit FloorReq(Request &request) {
        try {
            boost::property_tree::ptree tree;
            std::stringstream ss;
            ss << request.body();
            boost::property_tree::read_json(ss, tree);
            floor = tree.get<std::string>("floor");
        }
        catch(std::exception const& e) {
            std::cerr << e.what() << std::endl;
        }
    }
};

#endif //HTTPSERVER_SERIALIZERS_H
