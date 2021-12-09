#pragma once
#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <sstream>
#include <queue>

#include "neighbour.h"
#include "database.h"

using namespace std;

class Graph {
public:
	void add_top(int _id);

	void add_edge(int id1, int id2, int time);

    bool del_top(int _id);

    bool del_edge(int id1, int id2);

    bool is_neighbours(int id1, int id2);

	pair<vector<int>, int> calculate_route(int location, int destination);

    void save_data();

    void load_data();
private:
	Neighbour* get_pointer(int id);

    void change_ptr(int id1, int id2);

	vector<Neighbour> data;
};
