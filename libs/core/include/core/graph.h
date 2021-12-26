#ifndef BMSTU_MAP_CORE_GRAPH_H
#define BMSTU_MAP_CORE_GRAPH_H

#include <algorithm>
#include <iostream>
#include <queue>
#include <sstream>
#include <tuple>
#include <vector>

#include "database.h"
#include "neighbour.h"
#include "ModelMap.hpp"

using Room = Core::Model::Map::Room;

class Graph {
public:
    Graph();

    Graph(const Core::Model::Map &model);

    void add_top(int _id);

    void add_top(int _id, Room* r);

    void add_edge(int id_l, int id_r, int time);

    bool del_top(int id);

    bool del_edge(int id_l, int id_r);

    bool is_neighbours(int id_l, int id_r);

    std::pair<std::vector<int>, int> calculate_route(int location,
                                                     int destination);

    std::pair<std::vector<Neighbour*>, int> calculate_route_(int location,
                                                     int destination);

    void save_data();

    void load_data();

private:
    Neighbour* get_pointer(int id);

    void move_top(std::vector<std::pair<int, int>>&, int id);

    std::vector<Neighbour> data;

    Database db;
};


#endif // BMSTU_MAP_CORE_GRAPH_H