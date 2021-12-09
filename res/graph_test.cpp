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

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}