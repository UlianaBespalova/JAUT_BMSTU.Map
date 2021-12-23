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
#include <QPixmap>

#include "mapController.h"

#define SCALECOEFFICIENT 0.005

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QWidget {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private:
  QListView *lvlFloor;
  QStringListModel *model;
  QLineEdit *leFrom;
  QLineEdit *leTo;
  QLineEdit *room;
  QPushButton *BuildButton;
  QPushButton *FindTmTblButtom;
  QLabel *timeTable;

  MapController *controller;

  bool pressed = false;
  QPoint prev_pos;

  
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

  void draw_example();
};
#endif // MAINWINDOW_H