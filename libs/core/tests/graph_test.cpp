#include <gtest/gtest.h>

#include "core/graph.h"

TEST(calculate_route_test_0, Assert_0) {
    Graph g;
    for (int i = 0; i < 7; i++) {
    g.add_top(i);
    }

    g.add_edge(0, 1, 2);
    g.add_edge(0, 2, 3);

    g.add_edge(1, 3, 3);
    g.add_edge(1, 4, 4);

    g.add_edge(2, 5, 2);

    g.add_edge(6, 5, 2);
    g.add_edge(6, 3, 2);
    g.add_edge(6, 4, 2);

    std::pair<std::vector<int>, int> r = g.calculate_route(0, 6);

    EXPECT_EQ(r.second, 7);

    g.add_edge(6, 0, 3);

    r = g.calculate_route(0, 6);

    EXPECT_EQ(r.second, 3);
}

TEST(calculate_route_test_1, Assert_1) {
    Graph g;
    for (int i = 0; i < 7; i++) {
    g.add_top(i);
    }

    g.add_edge(0, 1, 2);
    g.add_edge(0, 2, 3);

    g.add_edge(1, 3, 3);
    g.add_edge(1, 4, 4);

    g.add_edge(2, 5, 2);

    g.add_edge(6, 5, 2);
    g.add_edge(6, 3, 2);
    g.add_edge(6, 4, 2);

    std::pair<std::vector<Neighbour*>, int> r = g.calculate_route_(0, 6);

    EXPECT_EQ(r.second, 7);

    g.add_edge(6, 0, 3);

    r = g.calculate_route_(0, 6);

    EXPECT_EQ(r.second, 3);
}
