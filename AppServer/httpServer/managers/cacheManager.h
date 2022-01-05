//
// Created by UlianaBespalova on 10.11.2021.
//
#ifndef CACHEMANAGER_H
#define CACHEMANAGER_H

#include "serializers.h"
#include "serverTypes.h"

class CacheManager {
public:
    CacheManager();

    mapType getSchedule(){};
    ScheduleListResponse getFacultyCache() const;

private:
    const std::string facultyCachePath = "managers/cacheData/cacheFaculty";
    ScheduleListResponse facultyCache;

    ScheduleListResponse loadFacultyCache() const;
};

#endif  // CACHEMANAGER_H
