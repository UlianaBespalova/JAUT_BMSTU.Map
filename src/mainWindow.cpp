#include "mainWindow.h"
#include "core/graph.h"

MainWindow::MainWindow(Core::Model::Map *map_model) : QWidget() {
  controller = new MapController();
  mapmodel = map_model;
  mapview = new Core::View::Map(mapmodel, controller->drawer);  this->setWindowIcon(QIcon("../image/map.png"));
  this->setWindowTitle("BMSTUMap");
  this->setStyleSheet("QWidget { "
                      "background-color: white ; "
                      "}");
  leTo = new QLineEdit();
  leFrom = new QLineEdit();
  leTo->setFixedWidth(100);
  leFrom->setFixedWidth(100);
  leFrom->setFixedHeight(35);
  leTo->setFixedHeight(35);
  leFrom->setStyleSheet("QLineEdit { "
                        "border: 1px solid black; "
                        "border-radius: 3px; "
                        "background-color: white; "
                        "font: 13pt 'Nocturno BG';"
                        "}");
  leTo->setStyleSheet("QLineEdit { "
                      "border: 1px solid black; "
                      "border-radius: 3px; "
                      "background-color: white; "
                      "font: 13pt 'Nocturno BG';"
                      "}");

  BuildButton = new QPushButton();
  BuildButton->setFixedSize(QSize(205, 35));
  BuildButton->setText("Построить путь");
  BuildButton->setStyleSheet("QPushButton { "
                             "border: 1px solid black; "
                             "border-radius: 3px; "
                             "font-size: 14pt;"
                             "font-family: 'Nocturno BG'; "
                             "background-color: #3f5eab; "
                             "color: white; "
                             "}");

  model = new QStringListModel();
  QStringList list;
  QString str;
  for (size_t i = 1; i < 10; i++) {
    str = QString("%1 этаж").arg(i);
    list << str;
  }
  model->setStringList(list);

  lvlFloor = new QListView();
  lvlFloor->setModel(model);
  lvlFloor->setEditTriggers(QAbstractItemView::NoEditTriggers);
  lvlFloor->setFixedHeight(list.size() * 32);
  lvlFloor->setFixedWidth(205);
  lvlFloor->setStyleSheet("QListView { "
                          "background-color: white; "
                          "border: 2px; "
                          "border-radius: 0px; "
                          "font: 13pt 'Nocturno BG'; "
                          "background: #f1f1f1"
                          "}"

                          "QListView::item {"
                          "border: 1.2px solid black; "
                          "border-radius: 3px; "
                          "margin-top: 4px; "
                          "text-align: right; "
                          "padding-top: 4px; "
                          "padding-left: 63px; "
                          "}"

                          "QListView::item:selected {"
                          "background: #2b76b4;"
                          "}");

  connect(lvlFloor->selectionModel(),
          SIGNAL(currentChanged(const QModelIndex, const QModelIndex)), this,
          SLOT(onLvFloorChanged(const QModelIndex, const QModelIndex)));

  connect(BuildButton, SIGNAL(pressed()), this, SLOT(onBuildPressed()));

  QLabel *lblFrom = new QLabel();
  lblFrom->setText("Откуда");
  lblFrom->setFixedSize(QSize(100, 20));
  lblFrom->setStyleSheet("QLabel { "
                         "background-color: white; "
                         "border: 0px; "
                         "border-radius: 0px; "
                         "font: 13pt 'Nocturno BG';"
                         "background: #f1f1f1;"
                         "};");

  QLabel *lblTo = new QLabel();
  lblTo->setText("Куда");
  lblTo->setFixedSize(QSize(100, 20));
  lblTo->setStyleSheet("QLabel { "
                       "background-color: white; "
                       "border: 0px; "
                       "border-radius: 0px; "
                       "font: 13pt 'Nocturno BG';"
                       "background: #f1f1f1;"
                       "};");

  room = new QLineEdit(this);
  room->setFixedWidth(205);
  room->setFixedHeight(35);
  room->setStyleSheet("QLineEdit { "
                      "border: 1px solid black; "
                      "border-radius: 3px; "
                      "background-color: white; "
                      "font: 13pt 'Nocturno BG';"
                      "}");

  FindTmTblButtom = new QPushButton(this);
  FindTmTblButtom->setFixedSize(QSize(205, 35));
  FindTmTblButtom->setText("Найти расписание");
  FindTmTblButtom->setStyleSheet("QPushButton { "
                                 "border: 1px solid black; "
                                 "border-radius: 3px; "
                                 "background-color: #3f5eab; "
                                 "color: white; "
                                 "font: 13pt 'Nocturno BG';"
                                 "}");
  QLabel *lblTmtbl = new QLabel();
  lblTmtbl->setText("Расписание");
  lblTmtbl->setFixedSize(QSize(200, 20));
  lblTmtbl->setStyleSheet("QLabel { "
                          "background-color: white; "
                          "border: 0px; "
                          "border-radius: 0px; "
                          "font: 13pt 'Nocturno BG';"
                          "background: #f1f1f1;"
                          "};");

  timeTable = new QLabel();
  int size = 1500 - leTo->size().height() * 3 - lvlFloor->size().height();
  timeTable->setFixedHeight(size);
  timeTable->setFixedWidth(205);
  timeTable->setStyleSheet("QLabel { "
                           "background-color: #f1f1f1; "
                           "border: 0px solid black; "
                           "border-top-width: 0px; "
                           "border-radius: 1px; "
                           "font: 13pt 'Nocturno BG';"
                           "};");

  connect(FindTmTblButtom, SIGNAL(pressed()), this,
          SLOT(onFindTmTblButtomPressed()));

  QVBoxLayout *vbox = new QVBoxLayout(this);
  QHBoxLayout *hbox1 = new QHBoxLayout();
  QHBoxLayout *hbox2 = new QHBoxLayout();

  hbox1->setSpacing(5);
  hbox1->addWidget(leFrom);
  hbox1->addWidget(leTo);
  hbox1->addStretch(1);

  hbox2->setSpacing(5);
  hbox2->addWidget(lblFrom);
  hbox2->addWidget(lblTo);
  hbox2->addStretch(0);

  vbox->setSpacing(5);
  vbox->addLayout(hbox2);
  vbox->addLayout(hbox1);
  vbox->addWidget(BuildButton);
  vbox->addWidget(lvlFloor, 1, Qt::AlignLeft);
  vbox->addStretch(1);
  vbox->addWidget(lblTmtbl);
  vbox->addWidget(room);
  vbox->addWidget(FindTmTblButtom);
  vbox->addWidget(timeTable);
  vbox->addStretch(0);

  QFrame *frame = new QFrame(this);
  frame->setLayout(vbox);
  frame->setGeometry(QRect(0, 0, 247, 1500));
  frame->setStyleSheet("QFrame { "
                       "background-color: white; "
                       "border: 1px solid black; "
                       "border-radius: 1px; "
                       "background: #f1f1f1;"
                       "};");
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
  bool okTo = false, okFrom = false;
  int from_id = leFrom->text().toInt(&okFrom);
  int to_id = leTo->text().toInt(&okTo);

  if (okTo and okFrom) {
      auto path = Graph(*mapmodel).calculate_route(from_id, to_id);

      // transform path into vector of points
      vector<Point> points;
      for (auto &neighbour : path.first) {
          Core::Geometry::geometry_t x_sum = 0, y_sum = 0;
          unsigned int p_num = 0;
          for (auto &wall: (*neighbour->room).getWalls()) {
              x_sum += wall.start.x;
              y_sum += wall.start.y; ++p_num;
              x_sum += wall.end.x;
              y_sum += wall.end.y; ++p_num;
          }
          Point p = { x_sum / p_num, y_sum / p_num };
          points.push_back(p);
      }

      mapview->setPath(points);
      update();
  }

  leTo->clear();
  leFrom->clear();
}

void MainWindow::onFindTmTblButtomPressed() {
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