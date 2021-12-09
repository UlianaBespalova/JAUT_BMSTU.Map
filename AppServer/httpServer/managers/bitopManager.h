//
// Created by UlianaBespalova on 10.11.2021.
//
#ifndef BITOPMANAGER_H
#define BITOPMANAGER_H

#include "httpClient.h"
#include "cacheManager.h"
#include "../serverTypes.h"

class BitopManager {
public:
    BitopManager(CacheManager *cacheManager, HttpClient *client) {}
    BitopManager() = default;

    ResponseString getSchedule(Request);
    std::string uploadData();

private:
    std::string token;
    HttpClient *client = new HttpClient();
    CacheManager *cacheManager = new CacheManager();
};

#endif //BITOPMANAGER_H
