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
    //Graph(const Graph&) = delete;
    //Graph(Graph&&) = delete;

    //Graph& operator= (const Graph&) = delete;
    //Graph& operator= (Graph&&) = delete;

	void add_top(int _id);

	void add_edge(int id1, int id2, int time);

    bool del_top(int _id);

    bool del_edge(int id1, int id2);

    bool is_neighbours(int id1, int id2);

	pair<vector<Neighbour*>, int> calculate_route(int _location, int _destination);

	pair<vector<Neighbour*>, int> calculate_route(Neighbour* location, Neighbour* destination);

private:
	Neighbour* get_pointer(int id);

    void change_ptr(int id1, int id2);

    void load_data();

    void save_data();

	vector<Neighbour> data;
};
