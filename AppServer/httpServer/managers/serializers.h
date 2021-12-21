//
// Created by UlianaBespalova on 29.11.2021.
//
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

#include "serverTypes.h"

#ifndef HTTPSERVER_SERIALIZERS_H
#define HTTPSERVER_SERIALIZERS_H

namespace ptree = boost::property_tree;

struct FloorReq {
    std::string floor;
    explicit FloorReq(Request& request) {
        try {
            ptree::ptree tree;
            std::stringstream ss;
            ss << request.body();
            ptree::read_json(ss, tree);
            floor = tree.get<std::string>("floor");
        } catch (std::exception const& e) {
            std::cerr << e.what() << std::endl;
        }
    }
};

struct ScheduleRequest {
    std::string group;
    explicit ScheduleRequest(Request& request) {
        try {
            ptree::ptree tree;
            std::stringstream ss;
            ss << request.body();
            ptree::read_json(ss, tree);
            group = tree.get<std::string>("group");
        } catch (std::exception const& e) {
            std::cerr << e.what() << std::endl;
        }
    }
};

struct ScheduleListResponse {
    int total;
    mapType itemList;

    explicit ScheduleListResponse(std::string& response) {
        try {
            ptree::ptree tree;
            std::stringstream ss;
            ss << response;
            ptree::read_json(ss, tree);
            total = tree.get<int>("total");
            ptree::ptree itemsArray = tree.get_child("items");
            ptree::ptree::iterator itemTree = itemsArray.begin();
            for (; itemTree != itemsArray.end(); ++itemTree) {
                std::string uuid = itemTree->second.get<std::string>("uuid");
                std::string caption = itemTree->second.get<std::string>("caption");
                itemList[caption] = uuid;
            }
        } catch (std::exception const& e) {
            std::cerr << e.what() << std::endl;
        }
    }
};

#endif  // HTTPSERVER_SERIALIZERS_H
