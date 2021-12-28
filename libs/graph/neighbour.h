#pragma once
#include <iostream>
#include <tuple>
#include <vector>

struct Neighbour {
    int id;
    std::vector<std::pair<int, int>> edge;
};