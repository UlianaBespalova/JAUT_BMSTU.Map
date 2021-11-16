//
// Created by UlianaBespalova on 10.11.2021.
//
#ifndef ROUTER_H
#define ROUTER_H

#include "bitopManager.h"
#include "mapManager.h"
#include "types.h"

class Router {
public:
    Router (BitopManager *bitopManager, MapManager *mapManager) {}
    Router() = default;
    responseType execute(requestType request) {}

private:
    BitopManager *bitopManager;
    MapManager *mapManager;
};

#endif //ROUTER_H
