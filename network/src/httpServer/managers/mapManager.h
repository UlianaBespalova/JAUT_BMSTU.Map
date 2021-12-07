//
// Created by UlianaBespalova on 10.11.2021.
//
#ifndef MAPMANAGER_H
#define MAPMANAGER_H

#include "../../baseClasses/types.h"

class MapManager {
public:
    MapManager() = default;

    mapType getMap() {};
    mapType getFloor(mapType) {};

    mapType getShortestPath(mapType);
};

#endif //MAPMANAGER_H
