#include "gtest/gtest.h"

#include "core/core.hpp"


using Core::Geometry::Point;

TEST(Point, create_simple) {
    Point p;
    p.x = 1;
    p.y = 2;
    EXPECT_EQ(p.x, 1);
    EXPECT_EQ(p.y, 2);
}

TEST(Point, create_initializer_list) {
    Point p = { 1, 2 };
    EXPECT_EQ(p.x, 1);
    EXPECT_EQ(p.y, 2);
}

TEST(Point, create_constructor) {
    Point p(1, 2);
    EXPECT_EQ(p.x, 1);
    EXPECT_EQ(p.y, 2);
}

TEST(Point, test_float) {
    Point p(2.354, 4.6221);
    EXPECT_DOUBLE_EQ(p.x, 2.354);
    EXPECT_DOUBLE_EQ(p.y, 4.6221);
}