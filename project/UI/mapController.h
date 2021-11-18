#ifndef MAPCONTROLLER_H
#define MAPCONTROLLER_H

#include "drawer.h"

class MapController {
public:
  MapController(Drawer *drawer);
  ~MapController();
  bool scale(double newScale);
  bool setFloor(int floor);
  bool viewMoveBy(Point shift);

private:
  Drawer *drawer;
};

#endif // MAPCONTROLLER_H