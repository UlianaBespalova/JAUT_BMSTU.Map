#ifndef DRAWER_H
#define DRAWER_H

#include <QPainter>
#include <QDebug>

struct Color {
    unsigned char r, g, b;
};

typedef double geometry_t;

struct Point {
    geometry_t x;
    geometry_t y;
};

class Drawer {
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
  void drawLine(Point start, Point end);
  void setFloor(int new_floor);
  void setScale(qreal new_scale);
  void setColor(Color &color);
  void setViewPos(Point new_pos);
  void drawText(std::string text, Point start);
  qreal getScale() const;
  Point getViewPos() const;

  QPainter *painter;
};

#endif // DRAWER_H