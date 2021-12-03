#include <gtest/gtest.h>

#include "graph.h"

TEST(calculate_route_test, Assert_0) {
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

	pair<vector<Neighbour*>, int> r = g.calculate_route(0, 6);

    EXPECT_EQ(r.second, 7);

    g.add_edge(6, 0, 3);

    r = g.calculate_route(0, 6);

    EXPECT_EQ(r.second, 3);
}

TEST(calculate_route_test1, Assert_1) {
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

    EXPECT_EQ(g.is_neighbours(0, 2), 1);
    EXPECT_EQ(g.is_neighbours(0, 6), 0);
}

TEST(calculate_route_test2, Assert_2) {
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

    pair<vector<Neighbour*>, int> r = g.calculate_route(0, 6);

    EXPECT_EQ(r.second, 7);

    g.add_edge(6, 0, 3);

    r = g.calculate_route(0, 6);

    EXPECT_EQ(r.second, 3);

    g.del_edge(0, 6);

    r = g.calculate_route(0, 6);

    EXPECT_EQ(r.second, 7);
}

TEST(calculate_route_test3, Assert_3) {
    Graph g;
    for (int i = 0; i < 9; i++) {
        g.add_top(i);
    }

    g.add_edge(0, 1, 2);
    g.add_edge(0, 2, 3);

    g.add_edge(1, 3, 3);
    g.add_edge(1, 4, 4);

    g.add_edge(2, 5, 2);

    g.add_edge(6, 5, 4);
    g.add_edge(6, 3, 3);
    g.add_edge(6, 4, 1);

    g.add_edge(8, 5, 1);

    pair<vector<Neighbour*>, int> r = g.calculate_route(0, 6);

    EXPECT_EQ(r.second, 7);

    g.del_top(4);

    r = g.calculate_route(0, 6);

    EXPECT_EQ(r.second, 8);

    g.del_top(1);

    r = g.calculate_route(0, 6);

    EXPECT_EQ(r.second, 9);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}