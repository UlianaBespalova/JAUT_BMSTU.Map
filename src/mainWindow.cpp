#include "mainWindow.h"

MainWindow::MainWindow(Core::Model::Map *map_model) : QWidget() {
  controller = new MapController();
  mapview = new Core::View::Map(map_model, controller->drawer);

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

  // Расписание
  // QVBoxLayout *vbox2 = new QVBoxLayout(this);
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

  connect(FindTmTblButtom, SIGNAL(pressed()), this, SLOT(onFindTmTblButtomPressed()));
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

void MainWindow::paintEvent(QPaintEvent *event) {
  Q_UNUSED(event);
  controller->drawer->painter = new QPainter(this);
  controller->drawer->painter->scale(controller->drawer->getScale(), controller->drawer->getScale());
  mapview->drawMap();
  controller->drawer->painter->end();
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
  if (event->button() == Qt::MouseButton::LeftButton) {
    qDebug() << "mouse pos - " << event->pos().x() << "  " << event->pos().y();
    this->pressed = true;
    this->prev_pos = event->pos();
  }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event) {
  if (this->pressed) {
    auto shift = event->pos() - this->prev_pos;
    controller->viewMoveBy(shift);
    this->prev_pos = event->pos();
    update();
  }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event) {
  if (event->button() == Qt::MouseButton::LeftButton)
    this->pressed = false;
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