#include "graph.h"

using namespace std;

void Graph::add_top(int _id) {
    if (get_pointer(_id) == nullptr){
        data.push_back({ _id, {} });
    }
}

void Graph::add_edge(int id1, int id2, int time) {
    if (is_neighbours(id1, id2)) {
        return;
    }
	Neighbour* ptr1 = get_pointer(id1);
	Neighbour* ptr2 = get_pointer(id2);
	if (ptr1 != nullptr && ptr2 != nullptr && id1 != id2) {
		ptr1->edge.push_back({ ptr2->id, time });
		ptr2->edge.push_back({ ptr1->id, time });
	}
}

Neighbour* Graph::get_pointer(int id) {
	for (auto& it : data) {
		if (it.id == id) {
			return &it;
		}
	}
	return nullptr;
}

bool Graph::is_neighbours(int id1, int id2) {
    Neighbour* ptr1 = get_pointer(id1);
    Neighbour* ptr2 = get_pointer(id2);

    for (auto& it: ptr1->edge) {
        if (it.first == ptr2->id) {
            return true;
        }
    }
    return false;
}

bool Graph::del_edge(int id1, int id2) {
    if (!is_neighbours(id1, id2)) {
        return false;
    }

    Neighbour* ptr1 = get_pointer(id1);
    Neighbour* ptr2 = get_pointer(id2);


    for (auto& it: ptr1->edge) {
        if (it.first == ptr2->id) {
            std::swap(it, ptr1->edge.back());
            ptr1->edge.pop_back();
            break;
        }
    }

    for (auto& it: ptr2->edge) {
        if (it.first == ptr1->id) {
            std::swap(it, ptr2->edge.back());
            ptr2->edge.pop_back();
            break;
        }
    }

    return true;
}

bool Graph::del_top(int _id) {
    Neighbour* ptr = get_pointer(_id);
    if (ptr == nullptr) {
        return false;
    }

    for (auto& it: ptr->edge) {
        Neighbour* ptr2 = get_pointer(it.first);
        for (auto& it_: ptr2->edge) {
            if (it_.first == ptr->id) {
                std::swap(it_, ptr2->edge.back());
                ptr2->edge.pop_back();
                break;
            }
        }
    }

    if (ptr != &data.back()) {
        //change_ptr(data.back().id, _id);
        std::swap(*ptr, data.back());
    }
    data.pop_back();

    return true;
}

pair<vector<int>, int> Graph::calculate_route(int location, int destination) {

	//Neighbour* location = get_pointer(_location);
	//Neighbour* destination = get_pointer(_destination);

	queue<pair<vector<int>, int>> route;
	route.push({ {location}, 0 });

	pair<vector<int>, int> result;
	bool route_found = false;

	while (!route.empty()) {
		pair<vector<int>, int> buffer = route.front();
		route.pop();

		if (route_found && result.second < buffer.second) {
			continue;
		}


		for (const auto& it : get_pointer(buffer.first.back())->edge) {
			pair<vector<int>, int> buf = buffer;
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


void Graph::load_data() {
    Database db;
    db.read_table(data);
    return;
}


void Graph::save_data() {
    Database db;
    for (const auto& it: data) {
        stringstream ss;
        cout << "SS " << ss.str() << endl;
        ss << it.id << ", ARRAY[";
        for (const auto &it_: it.edge) {
            ss << "[" << it_.first << ", " << it_.second << "]";
            if (it_ != it.edge.back()) {
                ss << ", ";
            }
        }
        ss << "]::integer[][]";
        db.insert_table(ss.str());
    }
    return;
}
