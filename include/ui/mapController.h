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

  inline int getFloor() { return drawer->getFloor(); }

public:
  Drawer *drawer;
};

#endif // MAPCONTROLLER_H