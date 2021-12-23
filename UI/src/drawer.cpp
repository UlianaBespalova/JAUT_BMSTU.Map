#include "drawer.h"

Drawer::Drawer() {
    view_pos.x = 0;
    view_pos.y = 0;
    floor = 0;
    QPen pen;
}

Drawer::~Drawer() {
 
}

QPoint Drawer::rePoint(Point &point) {
    return QPoint(point.x*scale + view_pos.x, point.y*scale + view_pos.y);
}

void Drawer::setFloor(int new_floor) {
    this->floor = new_floor;
}

void Drawer::setScale(qreal new_scale) {
    this->scale = new_scale;
}

void Drawer::drawLine(Point start, Point end) {
    pen.setWidth(5);
    painter->setPen(pen);
    QBrush brush;
    painter->setBrush(brush);
    painter->drawLine(rePoint(start), rePoint(end));
}

void Drawer::setColor(Color &color) {
    pen.setColor(QColor(color.r, color.g, color.b));
}

void Drawer::setViewPos(Point new_pos) {
    view_pos.x = new_pos.x;
    view_pos.y = new_pos.y;
}

void Drawer::drawText(std::string text, Point start) {
    painter->setPen(pen);
    painter->drawText(rePoint(start), QString::fromStdString(text));
}


qreal Drawer::getScale() const {
    return scale;
}


Point Drawer::getViewPos() const {
    return view_pos;
}
