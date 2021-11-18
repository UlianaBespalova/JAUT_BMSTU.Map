//
// Created by UlianaBespalova on 10.11.2021.
//
#ifndef BITOPMANAGER_H
#define BITOPMANAGER_H

#include "httpClient.h"
#include "cacheManager.h"
#include "../../baseClasses/types.h"

class BitopManager {
public:
    BitopManager(CacheManager *cacheManager, HttpClient *client) {}
    BitopManager() = default;

    Response getSchedule(mapType) {};

private:
    std::string token;
    HttpClient *client;
    CacheManager *cacheManager;
};

#endif //BITOPMANAGER_H
