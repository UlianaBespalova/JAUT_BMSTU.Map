#ifndef DRAWER_H
#define DRAWER_H

#include <QDebug>
#include <QPainter>

#include "core/ViewMap.hpp"
#include "core/geometry.hpp"

using Core::Geometry::Point;
using Core::View::Color;

class Drawer : public Core::View::IDrawer {
private:
  Point view_pos;
  int floor;
  qreal scale = 1;
  QPoint *matrix;

  QPen pen;
  QBrush brush;

  QPoint rePoint(Point &point);

public:
  Drawer();
  ~Drawer();
  void drawLine(Point start, Point end) override;
  void drawPolygon(Point *points, int pointCount);
  void drawImage(Point start, std::string path);
  void drawText(std::string text, Point start);
  void setFloor(int new_floor);
  void setScale(qreal new_scale);
  void setColor(Color color);
  void setBrushColor(Color &color);
  void setViewPos(Point new_pos);
  qreal getScale();
  Point getViewPos();

  QPainter *painter;
};

#endif // DRAWER_H