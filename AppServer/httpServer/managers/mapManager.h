//
// Created by UlianaBespalova on 10.11.2021.
//
#ifndef MAPMANAGER_H
#define MAPMANAGER_H

#include "../serverTypes.h"
#include "serializers.h"


typedef std::map<std::string, std::string> Params;

class MapManager {
public:
    MapManager() = default;

    ResponseString getMap();
    ResponseString getFloor(Request);
};

#endif //MAPMANAGER_H
