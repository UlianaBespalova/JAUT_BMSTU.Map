#include "mainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {
  controller = new MapController();

  setWindowTitle("BMSTUMap");

  this->setStyleSheet("QWidget { "
                      "background-color: #EEE9E9 ; "
                      "}");

  QVBoxLayout *vbox = new QVBoxLayout(this);
  QHBoxLayout *hbox = new QHBoxLayout();

  leTo = new QLineEdit();
  leFrom = new QLineEdit();
  leTo->setFixedWidth(60);
  leFrom->setFixedWidth(60);
  leFrom->setStyleSheet("QLineEdit { "
                        "border: 1px solid black; "
                        "border-radius: 2px; "
                        "background-color: white; "
                        "}");
  leTo->setStyleSheet("QLineEdit { "
                      "border: 1px solid black; "
                      "border-radius: 2px; "
                      "background-color: white; "
                      "}");

  BuildButton = new QPushButton();
  BuildButton->setFixedSize(QSize(24, 21));

  BuildButton->setStyleSheet("QPushButton { "
                             "border: 1px solid black; "
                             "border-radius: 2px; "
                             "background-color: white; "
                             "}");

  hbox->setSpacing(0);
  hbox->addWidget(leTo);
  hbox->addWidget(leFrom);
  hbox->addWidget(BuildButton);
  hbox->addStretch(1);

  model = new QStringListModel();
  QStringList list;
  QString str;
  for (size_t i = 1; i < 10; i++) {
    str = QString("%1 этаж").arg(i);
    list << str;
  }

  model->setStringList(list);

  lvlFloor = new QListView(this);
  lvlFloor->setModel(model);
  lvlFloor->setEditTriggers(QAbstractItemView::NoEditTriggers);
  lvlFloor->setFixedHeight(list.size() * 22);
  lvlFloor->setFixedWidth(145);

  lvlFloor->setStyleSheet("QListView { "
                          "background-color: white; "
                          "border: 1px solid black; "
                          "border-radius: 2px; "
                          "font: 10.5pt 'Helvetica';"
                          "};"
                          "QListView::item:selected {"
                          "border: 1px;"
                          "};");

  vbox->setSpacing(0);
  vbox->addLayout(hbox);
  vbox->addWidget(lvlFloor, 1, Qt::AlignLeft);
  vbox->addStretch(1);

  connect(lvlFloor->selectionModel(),
          SIGNAL(currentChanged(const QModelIndex, const QModelIndex)), this,
          SLOT(onLvFloorChanged(const QModelIndex, const QModelIndex)));

  connect(BuildButton, SIGNAL(pressed()), this, SLOT(onBuildPressed()));

  QHBoxLayout *hbox2 = new QHBoxLayout();

  room = new QLineEdit(this);
  room->setFixedWidth(126);
  room->setStyleSheet("QLineEdit { "
                      "border: 1px solid black; "
                      "border-radius: 2px; "
                      "background-color: white; "
                      "}");

  FindTmTblButtom = new QPushButton(this);
  FindTmTblButtom->setFixedSize(QSize(24, 21));
  FindTmTblButtom->setStyleSheet("QPushButton { "
                                 "border: 1px solid black; "
                                 "border-radius: 2px; "
                                 "background-color: white; "
                                 "}");

  hbox2->addWidget(room, 1, Qt::AlignRight);
  hbox2->addWidget(FindTmTblButtom);

  timeTable = new QLabel();
  timeTable->setFixedHeight(145);
  timeTable->setFixedWidth(150);
  timeTable->setStyleSheet("QLabel { "
                           "background-color: white; "
                           "border: 1px solid black; "
                           "border-radius: 2px; "
                           "font: 10.5pt 'Helvetica';"
                           "};"
                           "QListView::item:selected {"
                           "border: 1px;"
                           "};");

  vbox->setSpacing(0);
  vbox->addLayout(hbox2);
  vbox->addWidget(timeTable, 1, Qt::AlignRight);

  connect(FindTmTblButtom, SIGNAL(pressed()), this,
          SLOT(onFindTmTblButtomPressed()));
}

MainWindow::~MainWindow() {
  delete lvlFloor;
  delete model;
  delete leFrom;
  delete leTo;
  delete BuildButton;

  delete controller;
}

void MainWindow::onLvFloorChanged(const QModelIndex, const QModelIndex) {
  controller->setFloor(lvlFloor->currentIndex().row());
}

void MainWindow::onBuildPressed() {
  qDebug() << "Build button pressed!  ";
  qDebug() << leTo->text() << "    " << leFrom->text();
  leTo->clear();
  leFrom->clear();
}

void MainWindow::onFindTmTblButtomPressed() {
  qDebug() << "Find timetable pressed!  ";
  QString data = "There will be a \ntimetable!";
  qDebug() << room->text();
  timeTable->setText(data);

  room->clear();
}

void MainWindow::draw_example(QPainter *p) {
  Point start;
  start.x = 400;
  start.y = 100;
  Point end;
  end.x = 400;
  end.y = 400;
  controller->drawer->drawLine(p, start, end);

  start.x = 400;
  start.y = 100;
  end.x = 600;
  end.y = 100;
  controller->drawer->drawLine(p, start, end);

  start.x = 600;
  start.y = 100;
  end.x = 600;
  end.y = 400;
  controller->drawer->drawLine(p, start, end);

  start.x = 600;
  start.y = 400;
  end.x = 400;
  end.y = 400;
  controller->drawer->drawLine(p, start, end);
}

void MainWindow::paintEvent(QPaintEvent *event) {
  Q_UNUSED(event);
  QPainter painter(this);
  painter.scale(controller->drawer->getScale(), controller->drawer->getScale());
  draw_example(&painter);
  painter.end();
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
  if (event->button() == Qt::MouseButton::LeftButton) {
    qDebug() << "mouse pos - " << event->pos().x() << "  " << event->pos().y();
    pressed = true;
    prev_pos = event->pos();
  }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event) {
  if (pressed) {
    auto shift = event->pos() - prev_pos;
    controller->viewMoveBy(shift);
    prev_pos = event->pos();
    update();
  }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event) {
  if (event->button() == Qt::MouseButton::LeftButton) {
    pressed = false;
  }
}

void MainWindow::mouseDoubleClickEvent(QMouseEvent *event) {
  qDebug() << "mouse double clecked - " << event->pos().x() << " "
           << event->pos().y();
}

void MainWindow::wheelEvent(QWheelEvent *event) {
  qreal scale = controller->drawer->getScale();
  scale += event->angleDelta().y() > 0 ? SCALECOEFFICIENT : -SCALECOEFFICIENT;
  controller->drawer->setScale(scale);
  update();
}