#include <gtest/gtest.h>

#include "graph.h"
#include "database.h"

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

TEST(del_edge_test, Assert_2) {
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

    g.del_edge(0, 6);

    r = g.calculate_route(0, 6);

    EXPECT_EQ(r.second, 7);
}

TEST(del_top_test, Assert_3) {
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

    std::pair<std::vector<int>, int> r = g.calculate_route(0, 6);

    EXPECT_EQ(r.second, 7);

    g.del_top(4);

    r = g.calculate_route(0, 6);

    EXPECT_EQ(r.second, 8);

    g.del_top(1);

    r = g.calculate_route(0, 6);

    EXPECT_EQ(r.second, 9);

}

TEST(save_data_test, Assert_4) {
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

    g.save_data();
}

TEST(load_data_test, Assert_5) {
    Graph g;
    g.load_data();

    std::pair<std::vector<int>, int> r = g.calculate_route(0, 6);

    EXPECT_EQ(r.second, 7);
}

TEST(insert_and_read_json_test, Assert_6) {
    std::string insert_string = "{\"count\": 7, \"query\": \"Victor Ivan\"}";

    Database json_db(JSON_TABLE_NAME, JSON_TABLE_FORMAT);
    json_db.insert_json(insert_string);
    std::string read_string = json_db.read_json();

    EXPECT_EQ(insert_string, read_string);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
