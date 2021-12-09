//
// Created by UlianaBespalova on 10.11.2021.
//
#ifndef CACHEMANAGER_H
#define CACHEMANAGER_H

#include "../serverTypes.h"

class CacheManager {
public:
    CacheManager() = default;

    mapType getSchedule() {};

private:
    std::vector<mapType> latestSchedule;
};

#endif //CACHEMANAGER_H
