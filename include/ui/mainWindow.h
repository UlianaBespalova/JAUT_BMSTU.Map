#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QHBoxLayout>
#include <QLineEdit>
#include <QListView>
#include <QLabel>
#include <QMouseEvent>
#include <QPushButton>
#include <QStringListModel>
#include <QVBoxLayout>
#include <QWheelEvent>
#include <QWidget>

#include "mapController.h"
#include "core/ModelMap.hpp"
#include "core/ViewMap.hpp"

class MainWindow : public QWidget {
  Q_OBJECT

public:
  explicit MainWindow(Core::Model::Map *model);
  ~MainWindow() override;

private:
  QListView *lvlFloor;
  QStringListModel *model;
  QLineEdit *leFrom, *leTo, *room;
  QPushButton *BuildButton, *FindTmTblButtom;
  QLabel *timeTable;

  MapController *controller;

  bool pressed = false;
  QPoint prev_pos;
  Core::View::Map *mapview;

protected:
  void paintEvent(QPaintEvent *event) override;

private slots:
  void onLvFloorChanged(const QModelIndex, const QModelIndex);
  void onBuildPressed();
  void onFindTmTblButtomPressed();
  void mousePressEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;
  void mouseReleaseEvent(QMouseEvent *event) override;
  void mouseDoubleClickEvent(QMouseEvent *event) override;
  void wheelEvent(QWheelEvent *event) override;
};
#endif // MAINWINDOW_H