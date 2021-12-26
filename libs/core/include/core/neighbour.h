#pragma once
#include <iostream>
#include <tuple>
#include <vector>
#include "ModelMap.hpp"

using Room = Core::Model::Map::Room;

struct Neighbour {
    int id;
    std::vector<std::pair<int, int>> edge;
    Room* room;
};