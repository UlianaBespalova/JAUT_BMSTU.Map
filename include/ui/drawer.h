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
  qreal scale = 1;
  QPoint *matrix;

  QPen pen;
  QBrush brush;

  QPoint rePoint(const Point &point) const;

public:
  Drawer();
  ~Drawer();

  void drawLine(Point start, Point end) override;
  void drawPolygon(const std::vector<Point> &points) override;
  void drawText(const std::string &text, Point start) override;
  void setLineColor(const Color &color) override;
  void setBrushColor(const Color &color) override;
  void drawImage(Point center, const std::string &path);

  void setScale(qreal new_scale);
  void setViewPos(Point new_pos);

  qreal getScale() const;
  Point getViewPos();

  QPainter *painter;
};

#endif // DRAWER_H