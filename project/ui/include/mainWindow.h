#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QStringListModel>
#include <QListView>
#include <QLineEdit>
#include <QMouseEvent>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWheelEvent>

#include "mapController.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    // Ui::MainWindow *ui;

    QListView *lvlFloor;
    QStringListModel *model;
    QLineEdit *leFrom, *leTo;
    QPushButton *BuildButton;

    QTimer *timer;
    MapController *controller;

protected:
    void paintEvent(QPaintEvent *event) override;

private slots:
    void onLvFloorChanged(const QModelIndex, const QModelIndex);
    void onBuildPressed();
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent * event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
};
#endif // MAINWINDOW_H