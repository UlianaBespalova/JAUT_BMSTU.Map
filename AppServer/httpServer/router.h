//
// Created by UlianaBespalova on 10.11.2021.
//
#ifndef ROUTER_H
#define ROUTER_H

#include <memory>

#include "bitopManager.h"
#include "mapManager.h"
#include "serverTypes.h"

class Router {
public:
    Router(BitopManager *bitopManager, MapManager *mapManager);
    Router() = default;
    virtual ~Router() = default;
    ResponseString execute(Request &request);

private:
    std::shared_ptr<BitopManager> bitopManager;
    std::shared_ptr<MapManager> mapManager;

    const std::string schedulePath = "/schedule";
    const std::string scheduleTestPath = "/schedule_test";
    const std::string mapPath = "/map";
};

#endif  // ROUTER_H
