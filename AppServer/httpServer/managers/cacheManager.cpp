//
// Created by UlianaBespalova on 10.11.2021.
//
#include "cacheManager.h"

#include <fstream>

CacheManager::CacheManager() : facultyCache(loadFacultyCache()) {}

ScheduleListResponse CacheManager::loadFacultyCache() const {
    std::ifstream ifs(facultyCachePath);
    std::string dataStr((std::istreambuf_iterator<char>(ifs)),
                        (std::istreambuf_iterator<char>()));
    return ScheduleListResponse(dataStr);
}

ScheduleListResponse CacheManager::getFacultyCache() const { return facultyCache; }
