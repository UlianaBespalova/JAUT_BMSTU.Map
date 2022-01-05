//
// Created by UlianaBespalova on 10.11.2021.
//
#ifndef BITOPMANAGER_H
#define BITOPMANAGER_H

#include <memory>
#include <utility>

#include "cacheManager.h"
#include "httpClient.h"
#include "serverTypes.h"

struct GroupParams {
    std::string faculty;
    std::string department;
    std::string group;
    GroupParams(std::string f, std::string d, std::string g)
            : faculty(std::move(f)), department(std::move(d)), group(std::move(g)) {}
};

class BitopManager {
public:
    BitopManager();

    ResponseString getSchedule(Request);
    ResponseString getSchedule_test();

private:
    std::string getScheduleForGroup(const GroupParams &groupParams);
    std::string getItemsByUuid(const std::string &uid, const std::string &type);
    std::string getScheduleByGroupUuid(const std::string &uid);

    const std::string bitopDomain = "api.bitop.bmstu.ru";
    const std::string bitopIP = "195.19.40.96";
    const unsigned short bitopPort = 443;

    const std::string scheduleListTarget = "/search/unit";
    const std::string scheduleTarget = "/schedule/";

    const std::string tokenHeader = "x-bb-token";
    const std::string token =
            "bb-at-1rrz8bvnkc5xb7lsx3ga4wpscn73qkfzc5h6ftr32s134";
    Params headers;

    std::shared_ptr<HttpsClient> client;
    std::shared_ptr<CacheManager> cacheManager;
};

#endif  // BITOPMANAGER_H
