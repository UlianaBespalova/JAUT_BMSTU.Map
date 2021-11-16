//
// Created by UlianaBespalova on 10.11.2021.
//
#ifndef CACHEMANAGER_H
#define CACHEMANAGER_H

#include "types.h"

class CacheManager {
public:
    CacheManager() = default;

    mapType getSchedule() {};

private:
    std::vector<mapType> latestSchedule;
};

#endif //CACHEMANAGER_H
