#include "graph.h"

Graph::Graph() : db(GRAPH_TABLE_NAME, GRAPH_TABLE_FORMAT) {}

void Graph::add_top(int id) {
    if (get_pointer(id) == nullptr) {
        data.push_back({id, {}});
    }
}

void Graph::add_edge(int id_l, int id_r, int time) {
    if (is_neighbours(id_l, id_r)) {
        return;
    }
    Neighbour* l = get_pointer(id_l);
    Neighbour* r = get_pointer(id_r);
    if (l != nullptr && r != nullptr && id_l != id_r) {
        l->edge.push_back({r->id, time});
        r->edge.push_back({l->id, time});
    }
}

Neighbour* Graph::get_pointer(int id) {
    auto is_equal_id{[&id](Neighbour n) { return id == n.id; }};

    std::vector<Neighbour>::iterator it =
            std::find_if(data.begin(), data.end(), is_equal_id);
    if (it != data.end()) {
        return &(*it);
    }

    return nullptr;
}

bool Graph::is_neighbours(int id_l, int id_r) {
    Neighbour* l = get_pointer(id_l);

    auto is_needed_id{[&id_r](std::pair<int, int> n) { return id_r == n.first; }};

    auto iter = std::find_if(l->edge.begin(), l->edge.end(), is_needed_id);
    if (iter != l->edge.end()) {
        return true;
    }

    return false;
}

void Graph::move_top(std::vector<std::pair<int, int>>& vec_edge, int id) {
    for (auto& it : vec_edge) {
        if (it.first == id) {
            std::swap(it, vec_edge.back());
            vec_edge.pop_back();
            break;
        }
    }
    return;
}

bool Graph::del_edge(int id_l, int id_r) {
    if (!is_neighbours(id_l, id_r)) {
        return false;
    }

    Neighbour* l = get_pointer(id_l);
    Neighbour* r = get_pointer(id_r);

    move_top(l->edge, id_r);
    move_top(r->edge, id_l);

    return true;
}

bool Graph::del_top(int id) {
    Neighbour* ptr = get_pointer(id);
    if (!ptr) {
        return false;
    }

    for (auto& it : ptr->edge) {
        Neighbour* neighbour = get_pointer(it.first);
        move_top(neighbour->edge, id);
    }

    if (ptr != &data.back()) {
        std::swap(*ptr, data.back());
    }
    data.pop_back();

    return true;
}

std::pair<std::vector<int>, int> Graph::calculate_route(int location,
                                                        int destination) {
    std::queue<std::pair<std::vector<int>, int>> route;
    route.push({{location}, 0});

    std::pair<std::vector<int>, int> result;
    bool route_found = false;

    while (!route.empty()) {
        std::pair<std::vector<int>, int> buffer = route.front();
        route.pop();

        if (route_found && result.second < buffer.second) {
            continue;
        }

        for (const auto& it : get_pointer(buffer.first.back())->edge) {
            std::pair<std::vector<int>, int> buf = buffer;
            if (std::find(buf.first.begin(), buf.first.end(), it.first) ==
                buf.first.end()) {
                buf.first.push_back(it.first);
                buf.second += it.second;
                route.push(buf);

                if (it.first == destination && !route_found) {
                    result = buf;
                    route_found = true;
                }

                if (it.first == destination && route_found &&
                    buf.second < result.second) {
                    result = buf;
                }
            }
        }
    }
    return result;
}

void Graph::load_data() {
    db.read_table(data);
    return;
}

void Graph::save_data() {
    for (const auto& it : data) {
        std::stringstream ss;
        ss << it.id << ", ARRAY[";
        for (const auto& it_ : it.edge) {
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
