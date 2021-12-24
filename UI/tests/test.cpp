#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "mainWindow.h"
#include "mapController.h"

TEST(Drawer, getScaleView) {
  Drawer drawer;
  EXPECT_NO_FATAL_FAILURE(drawer.getViewPos());
  EXPECT_NO_FATAL_FAILURE(drawer.getScale());
}

TEST(Drawer, setParams) {
  Drawer drawer;
  Color c;
  c.r = 100;
  c.g = 100;
  c.b = 100;
  Point p;
  p.x = 100;
  p.y = -200;
  EXPECT_NO_FATAL_FAILURE(drawer.setColor(c));
  EXPECT_NO_FATAL_FAILURE(drawer.setFloor(3));
  EXPECT_NO_FATAL_FAILURE(drawer.setScale(1.2));
  EXPECT_NO_FATAL_FAILURE(drawer.setViewPos(p));
}

TEST(MapController, Scale) {
  double new_scale = 0.3;
  MapController controller;
  EXPECT_EQ(controller.scale(new_scale), true);
}

TEST(MapController, ViewMoveByEmpy) {
  MapController controller;
  EXPECT_EQ(controller.viewMoveBy(QPoint(100, 100)), true);
}

TEST(MapController, SetFloor) {
  MapController controller;
  EXPECT_EQ(controller.setFloor(4), true);
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}