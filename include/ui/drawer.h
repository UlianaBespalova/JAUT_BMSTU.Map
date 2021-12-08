#ifndef DRAWER_H
#define DRAWER_H

#include <QPainter>
#include <QDebug>

#include "core/geometry.hpp"
#include "core/ViewMap.hpp"


using Core::Geometry::Point;
using Core::View::Color;

class Drawer : public Core::View::IDrawer {
private:
  Point view_pos;
  int floor;
  qreal scale = 1;
  QPoint *matrix;

  QPen pen;

  QPoint rePoint(Point &point);

public:
  Drawer();
  ~Drawer();
  void drawLine(Point start, Point end) override;
  void setFloor(int new_floor);
  void setScale(qreal new_scale);
  void setColor(Color color) override;
  void setViewPos(Point new_pos);
  qreal getScale();
  Point getViewPos();

  QPainter *painter;
};

#endif // DRAWER_H