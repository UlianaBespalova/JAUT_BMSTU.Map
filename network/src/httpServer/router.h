//
// Created by UlianaBespalova on 10.11.2021.
//
#ifndef ROUTER_H
#define ROUTER_H

#include "managers/bitopManager.h"
#include "managers/mapManager.h"
#include "baseClasses/types.h"

class Router {
public:
    Router (BitopManager *bitopManager, MapManager *mapManager) {}
    Router() = default;
    Response execute(Request request) {}

private:
    BitopManager *bitopManager;
    MapManager *mapManager;
};

#endif //ROUTER_H
