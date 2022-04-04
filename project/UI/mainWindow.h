#ifndef MAINWIMDOW_H
#define MAINWIMDOW_H

#include <QLineEdit>
#include <QMainWindow>
#include <QPushButton>
#include <QListView>

#include "mapController.h"
#include "MapView.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(Qwidget *parent = nullptr);
  MainWindow(View::Map *view, MapController *controller);
  ~MainWindow();

protected:
  void onMousePress(QMouseEvent *event);
  void onMouseMove(QMouseEvent *event);
  void onMouseRelease(QMouseEvent *event);
  void onMouseDoubleClick(QMouseEvent *event);
  void onMouseWheel(QWheelEvent *event);
  void onBuildPressed();
  void onLvFloorChanged();
  void onStart();

private:
  Ui::MainWindow *ui;
  QLineEdit *leFrom, *LleTo;
  QPushButton *BuildButton;
  QListView *lvFloors;

  View::Map *map_view;
  MapController *map_controller;
};
#endif // MAINWINDOW_H
