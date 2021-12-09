#pragma once
#include <iostream>
#include <vector>
#include <tuple>

struct Neighbour {
    int id;
    std::vector<std::pair<int, int>> edge;
};