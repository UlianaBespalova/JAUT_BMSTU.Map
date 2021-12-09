#ifndef BMSTU_MAP_CORE_GRAPH_H
#define BMSTU_MAP_CORE_GRAPH_H

#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <queue>

#include "ModelMap.hpp"

using namespace std;
using namespace Core;
using Room = Model::Map::Room;


class Graph {
public:
    struct Neighbour {
        int id;
        vector<pair<Neighbour*, int>> edge;
        Room *room;
    };

    explicit Graph(const Model::Map &model) {
        auto &rooms = model.getRooms();
        int id = 0;
        for (auto &room : rooms)
            add_top(id++, const_cast<Room *>(&room));  // TODO: fix const

        for (int i = 1; i < rooms.size(); ++i)
            add_edge(0, i, 10);
    }

	void add_top(int _id, Room *r);
	void add_edge(int id1, int id2, int time);

	pair<vector<Neighbour*>, int> calculate_route(int _location, int _destination);
	pair<vector<Neighbour*>, int> calculate_route(Neighbour* location, Neighbour* destination);

private:
	Neighbour* get_pointer(int id);
	vector<Neighbour> data;
};

#endif // BMSTU_MAP_CORE_GRAPH_H