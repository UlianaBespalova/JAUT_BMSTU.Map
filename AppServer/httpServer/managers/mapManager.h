//
// Created by UlianaBespalova on 10.11.2021.
//
#ifndef MAPMANAGER_H
#define MAPMANAGER_H

#include <memory>

#include "graph/database.h"
#include "serializers.h"
#include "serverTypes.h"

class MapManager {
public:
    MapManager() = default;

    ResponseString getMap() const;
private:
    const std::string jsonTableName = "map_table";
    const std::string jsonTableFormat = "doc jsonb PRIMARY KEY NOT NULL";

    std::shared_ptr<Database> database(jsonTableName, jsonTableFormat);
};

#endif  // MAPMANAGER_H
