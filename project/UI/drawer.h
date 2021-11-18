#ifndef DRAWER_H
#define DRAWER_H

#include "IDrawer.h"

class Drawer : public IDrawer {
private:
  Point view_pos;
  double scale = 1;

  Point rePoint(Point &point);

public:
  Drawer();
  ~Drawer();
  void drawLine(Point start, Point end);
  void setColor(Color color);
};

#endif // DRAWER_H