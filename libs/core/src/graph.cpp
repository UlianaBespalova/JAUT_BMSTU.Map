#include "graph.h"

using namespace std;

void Graph::add_top(int _id, Model::Map::Room *r) {
    if (get_pointer(_id) == nullptr){
        data.push_back({ _id, {}, r });
    }
}

void Graph::add_edge(int id1, int id2, int time) {
	Neighbour* ptr1 = get_pointer(id1);
	Neighbour* ptr2 = get_pointer(id2);
	if (ptr1 != nullptr && ptr2 != nullptr) {
		ptr1->edge.emplace_back( ptr2, time );
		ptr2->edge.emplace_back( ptr1, time );
	}
}

Graph::Neighbour* Graph::get_pointer(int id) {
	for (auto& it : data) {
		if (it.id == id) {
			return &it;
		}
	}
	return nullptr;
}

pair<vector<Graph::Neighbour*>, int> Graph::calculate_route(int _location, int _destination) {

	Neighbour* location = get_pointer(_location);
	Neighbour* destination = get_pointer(_destination);


	queue<pair<vector<Neighbour*>, int>> route;
	route.push({ {location}, 0 });

	pair<vector<Neighbour*>, int> result;
	bool route_found = false;

	while (!route.empty()) {
		pair<vector<Neighbour*>, int> buffer = route.front();
		route.pop();

		if (route_found && result.second < buffer.second) {
			continue;
		}

		for (const auto& it : buffer.first.back()->edge) {
			pair<vector<Neighbour*>, int> buf = buffer;
			if (find(buf.first.begin(), buf.first.end(), it.first) == buf.first.end()) {
				buf.first.push_back(it.first);
				buf.second += it.second;
				route.push(buf);

				if (it.first == destination && !route_found) {
					result = buf;
					route_found = true;
				}

				if (it.first == destination && route_found && buf.second < result.second) {
					result = buf;
				}
			}
		}

	}
	return result;
}
