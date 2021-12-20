#ifndef MAPCONTROLLER_H
#define MAPCONTROLLER_H

#include "drawer.h"

class MapController {
public:
  MapController();
  ~MapController();

  bool scale(double newScale);
  bool setFloor(int newfloor);
  bool viewMoveBy(QPoint shift);

public:
  Drawer *drawer;
};

#endif // MAPCONTROLLER_H