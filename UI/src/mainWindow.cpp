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
  list << "1 этаж"
       << "2 этаж"
       << "3 этаж"
       << "4 этаж";
  list << "5 этаж"
       << "6 этаж"
       << "7 этаж"
       << "8 этаж"
       << "9 этаж";
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
  qDebug() << "Lvl changed ";
  qDebug() << lvlFloor->currentIndex().row();
}

void MainWindow::onBuildPressed() {
  qDebug() << "Build button pressed!  ";
  qDebug() << leTo->text().toInt() << "    " << leFrom->text().toInt();
  leTo->clear();
  leFrom->clear();
}

void MainWindow::paintEvent(QPaintEvent *event) {
  Q_UNUSED(event);
  QPainter painter(this);
  painter.scale(controller->drawer->getScale(),
                 controller->drawer->getScale());

  Point start;
  start.x = 400;
  start.y = 100;
  Point end;
  end.x = 400;
  end.y = 400;
  controller->drawer->drawLine(&painter, start, end);

  start.x = 400;
  start.y = 100;
  end.x = 600;
  end.y = 100;
  controller->drawer->drawLine(&painter, start, end);

  start.x = 600;
  start.y = 100;
  end.x = 600;
  end.y = 400;
  controller->drawer->drawLine(&painter, start, end);

  start.x = 600;
  start.y = 400;
  end.x = 400;
  end.y = 400;
  controller->drawer->drawLine(&painter, start, end);
  painter.end();
}

void MainWindow::mousePressEvent(QMouseEvent *event) {

  qDebug() << "mouse pos - " << event->pos().x() << "  " << event->pos().y();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event) {
  controller->viewMoveBy(event->pos());
  setUpdatesEnabled(false);
  update();
  setUpdatesEnabled(true);
}

void MainWindow::mouseDoubleClickEvent(QMouseEvent *event) {
  qDebug() << "mouse double clecked - " << event->pos().x() << " "
           << event->pos().y();
}

void MainWindow::wheelEvent(QWheelEvent *event) {
  qreal scale = controller->drawer->getScale();
  scale += event->angleDelta().y() > 0 ? 0.005 : -0.005;
  controller->drawer->setScale(scale);
  update();
}