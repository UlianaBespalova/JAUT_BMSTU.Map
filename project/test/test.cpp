#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "mainWindow.h"
#include "mapController.h"

class MockMainWindow : public MainWindow {
public:
  MockMainWindow(Qwidget *parent = nullptr);
protected:
  MOCK_METHOD(void, onBuildPressed, ());
  MOCK_METHOD(void, onLvFloorChanged, ());
  MOCK_METHOD(void, onStart, ());
}

TEST(MainWindow, event) {
    MockMainWindow window;
    EXPECT_CALL(window, onBuildPressed()).Times(::testing::AnyNumber());
    EXPECT_CALL(window, onLvFloorChanged()).Times(::testing::AnyNumber());
    EXPECT_CALL(window, onStart()).Times(::testing::AnyNumber());
}

TEST(MapController, Scale) {
  double scale = 0.3 : EXPECT_EQ(scale(scale), true);
}

TEST(MapController, ViewMoveByEmpy) { EXPECT_EQ(viewMoveBy(0), false); }

TEST(MapController, ViewMoveBy) {
  struct Vector {
    double x;
    double y;
  };

  typedef Vector Point;

  Point p;
  p.x = 12;
  p.y = 13;

  EXPECT_EQ(viewMoveBy(p), false);
}

TEST(MapController, SetFloor) { EXPECT_EQ(setFloor(4), true); }

TEST(MapController, SetFloor) {
    EXPECT_EQ(setFloor(-100, false);
}

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}