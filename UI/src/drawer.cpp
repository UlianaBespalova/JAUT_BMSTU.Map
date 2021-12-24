#include "drawer.h"

Drawer::Drawer() {
  view_pos.x = 0;
  view_pos.y = 0;
  floor = 0;
  QPen pen;
  QBrush brush;
}

Drawer::~Drawer() {}

QPoint Drawer::rePoint(Point &point) {
  return QPoint(point.x * scale + view_pos.x, point.y * scale + view_pos.y);
}

void Drawer::setFloor(int new_floor) { this->floor = new_floor; }

void Drawer::setScale(qreal new_scale) { this->scale = new_scale; }

void Drawer::drawPolygon(Point *points, int pointCount) {
  pen.setWidth(5);
  Color c;
  c.r = 234;
  c.g = 130;
  c.b = 23;
  Color c2;
  c2.r = 120;
  c2.g = 172;
  c2.b = 236;
  setPenColor(c);
  setBrushColor(c2);
  brush.setStyle(Qt::SolidPattern);
  painter->setPen(pen);
  painter->setBrush(brush);
  QPoint qpoints[pointCount];
  for (size_t i = 0; i < pointCount; i++) {
    qpoints[i] = rePoint(points[i]);
  }
  painter->drawPolygon(qpoints, pointCount);
}

void Drawer::drawLine(Point start, Point end) {
  pen.setWidth(5);
  painter->setPen(pen);
  painter->drawLine(rePoint(start), rePoint(end));
}

void Drawer::drawImage(Point start, std::string path) {
  QImage image(QString::fromStdString(path));
  if (!image.isNull()) {
    image = image.scaled(image.size().width() * scale,
                         image.size().height() * scale);
    painter->drawImage(rePoint(start), image);
  }
  else {
      qDebug() << "Image not found";
  }
}

void Drawer::setPenColor(Color &color) {
  pen.setColor(QColor(color.r, color.g, color.b));
}

void Drawer::setBrushColor(Color &color) {
  brush.setColor(QColor(color.r, color.g, color.b));
  brush.setStyle(Qt::SolidPattern);
}

void Drawer::setViewPos(Point new_pos) {
  view_pos.x = new_pos.x;
  view_pos.y = new_pos.y;
}

void Drawer::drawText(std::string text, Point start) {
  painter->setPen(pen);
  painter->drawText(rePoint(start), QString::fromStdString(text));
}

qreal Drawer::getScale() const { return scale; }

Point Drawer::getViewPos() const { return view_pos; }
