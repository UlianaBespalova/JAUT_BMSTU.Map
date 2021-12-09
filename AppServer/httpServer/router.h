//
// Created by UlianaBespalova on 10.11.2021.
//
#ifndef ROUTER_H
#define ROUTER_H

#include "bitopManager.h"
#include "mapManager.h"
#include "serverTypes.h"

class Router {
public:
    Router (BitopManager *bitopManager, MapManager *mapManager);
    Router() = default;
    virtual ~Router() = default;
    ResponseString execute(Request& request);

private:
    BitopManager *bitopManager = new BitopManager();
    MapManager *mapManager = new MapManager();
};

#endif //ROUTER_H
