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

	pair<vector<int>, int> r = g.calculate_route(0, 6);

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

    pair<vector<int>, int> r = g.calculate_route(0, 6);

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

    pair<vector<int>, int> r = g.calculate_route(0, 6);

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

    pair<vector<int>, int> r = g.calculate_route(0, 6);

    EXPECT_EQ(r.second, 7);
}

TEST(insert_json_test, Assert_6) {
    string s = "{\"query\": \"Victor Ivan\", \"count\": 7}";
    s = "{\n  \"floors\": [\n    {\n      \"floor\": 5,\n      \"rooms\": [\n        {\n          \"type\": 2,\n          \"walls\": [\n            { \"start\": [100, 100], \"end\": [100, 250] },\n            { \"start\": [100, 250], \"end\": [700, 250] },\n            { \"start\": [700, 250], \"end\": [700, 100] },\n            { \"start\": [700, 100], \"end\": [100, 100] }\n          ],\n          \"properties\": {\n            \"description\": \"Main hallway\"\n          }\n        },\n        {\n          \"type\": 1,\n          \"walls\": [\n            { \"start\": [100, 250], \"end\": [100, 350] },\n            { \"start\": [100, 350], \"end\": [200, 350] },\n            { \"start\": [200, 350], \"end\": [200, 250] },\n            { \"start\": [200, 250], \"end\": [175, 250] },\n            { \"start\": [175, 250], \"end\": [125, 250], \"type\": 2 },\n            { \"start\": [125, 250], \"end\": [100, 250] }\n          ],\n          \"properties\": {\n            \"description\": \"W\/C\",\n            \"gender\": \"F\"\n          }\n        }\n      ]\n    }\n  ]\n}";
    cout << s << endl;

    Database db(JSON_TABLE_NAME, JSON_TABLE_FORMAT);
    db.insert_json(s);

}

TEST(read_json_test, Assert_7) {
    string s;
    Database db(JSON_TABLE_NAME, JSON_TABLE_FORMAT);
    db.read_json(s);

}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}