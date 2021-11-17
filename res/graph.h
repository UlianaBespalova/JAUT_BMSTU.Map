#pragma once
#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <queue>

using namespace std;

struct Neighbour {
	int id;
	vector<pair<Neighbour*, int>> edge;
};

class Graph {
public:
	void add_top(int _id);

	void add_edge(int id1, int id2, int time);

	pair<vector<Neighbour*>, int> calculate_route(int _location, int _destination);

	pair<vector<Neighbour*>, int> calculate_route(Neighbour* location, Neighbour* destination);

private:
	Neighbour* get_pointer(int id);
	vector<Neighbour> data;
};
