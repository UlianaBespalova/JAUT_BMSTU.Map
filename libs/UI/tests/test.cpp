#include <gtest/gtest.h>
// #include <gmock/gmock.h>

// #include "mainWindow.h"
// #include "mapController.h"

// class MockMainWindow : public MainWindow {
// public:
//   MockMainWindow(Qwidget *parent = nullptr);
// protected:
//   MOCK_METHOD(void, onBuildPressed, ());
//   MOCK_METHOD(void, onLvFloorChanged, ());
// }

// TEST(MainWindow, event) {
//     MockMainWindow window;
//     EXPECT_CALL(window, onBuildPressed()).Times(::testing::AnyNumber());
//     EXPECT_CALL(window, onLvFloorChanged()).Times(::testing::AnyNumber());
// }

// TEST(MapController, Scale) {
//   double new_scale = 0.3 ;
//   EXPECT_EQ(scale(new_scale), true);
// }

// TEST(MapController, ViewMoveByEmpy) { EXPECT_EQ(viewMoveBy(QPoint(0, 1)), true); }

// TEST(MapController, ViewMoveBy) {
//   QPoint p;
//   p.x(12);
//   p.y(13);

//   EXPECT_EQ(viewMoveBy(p), false);
// }

// TEST(MapController, SetFloor) { EXPECT_EQ(setFloor(4), true); }

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}