#include "mainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {
  controller = new MapController();

  setWindowTitle("BMSTUMap");

  this->setStyleSheet("QWidget { "
                      "background-color: #d0cfcf ; "
                      "}");
  this->resize(800, 600);
  size_t height = this->size().height();

  QVBoxLayout *vbox = new QVBoxLayout(this);
  QHBoxLayout *hbox = new QHBoxLayout();

  leTo = new QLineEdit();
  leFrom = new QLineEdit();
  leTo->setFixedWidth(60);
  leTo->setPlaceholderText("Ввод...");
  leFrom->setPlaceholderText("Ввод...");
  leFrom->setFixedWidth(60);
  leFrom->setFixedHeight(20);
  leTo->setFixedHeight(20);
  leFrom->setStyleSheet("QLineEdit { "
                        "border: 0.3px solid black; "
                        "border-radius: 0.1px; "
                        "background-color: white; "
                        "font: 10.5pt 'Helvetica';"
                        "}");
  leTo->setStyleSheet("QLineEdit { "
                      "border: 0.3px solid black; "
                      "border-radius: 0.1px; "
                      "background-color: white; "
                      "font: 10.5pt 'Helvetica';"
                      "}");

  QPixmap pix("../media/search.png");
  QIcon icon(pix);
  BuildButton = new QPushButton();
  BuildButton->setFixedSize(QSize(24, 20));
  BuildButton->setIcon(icon);

  BuildButton->setStyleSheet("QPushButton { "
                             "border: 0.3px solid black; "
                             "border-radius: 0.1px; "
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
                          "border: 0.3px solid black; "
                          "border-radius: 0.1px; "
                          "font: 10.5pt 'Helvetica';"
                          "border-top-width: 1px; "
                          "border-bottom-width: 2px; "
                          "};"
                          "QListView::item:selected {"
                          "border: 0.1px;"
                          "};");

  connect(lvlFloor->selectionModel(),
          SIGNAL(currentChanged(const QModelIndex, const QModelIndex)), this,
          SLOT(onLvFloorChanged(const QModelIndex, const QModelIndex)));

  connect(BuildButton, SIGNAL(pressed()), this, SLOT(onBuildPressed()));

  QHBoxLayout *hbox2 = new QHBoxLayout();

  room = new QLineEdit(this);
  room->setPlaceholderText("Ввод...");
  room->setFixedWidth(120);
  room->setFixedHeight(20);
  room->setStyleSheet("QLineEdit { "
                      "border: 0.3px solid black; "
                      "border-radius: 0.1px; "
                      "background-color: white; "
                      "font: 10.5pt 'Helvetica';"
                      "}");

  FindTmTblButtom = new QPushButton(this);
  FindTmTblButtom->setFixedSize(QSize(24, 20));
  FindTmTblButtom->setIcon(icon);
  FindTmTblButtom->setStyleSheet("QPushButton { "
                                 "image: url(/media/search.png);"
                                 "border: 0.3px solid black; "
                                 "border-radius: 0.1px; "
                                 "background-color: white; "
                                 "font: 10.5pt 'Helvetica';"
                                 "}");

  hbox2->setSpacing(0);
  hbox2->addWidget(room);
  hbox2->addWidget(FindTmTblButtom, 1, Qt::AlignLeft);

  timeTable = new QLabel();
  timeTable->setFixedHeight(140);
  timeTable->setFixedWidth(145);
  timeTable->setStyleSheet("QLabel { "
                           "background-color: white; "
                           "border: 0.3px solid black; "
                           "border-top-width: 1px; "
                           "border-radius: 0.1px; "
                           "font: 10.5pt 'Helvetica';"
                           "};");

  QString data = "Введите группу для \nпоиска расписания!";
  timeTable->setText(data);

  vbox->setSpacing(0);
  vbox->addLayout(hbox);
  vbox->addWidget(lvlFloor, 1, Qt::AlignLeft);
  vbox->addLayout(hbox2);
  vbox->addWidget(timeTable, 1, Qt::AlignLeft);
  vbox->addStretch(1);

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
  QString data = "Расписание!!!!";
  qDebug() << room->text();
  timeTable->setText(data);

  room->clear();
}

void MainWindow::draw_example() {
  Point start;
  start.x = 200;
  start.y = 200;
  Point end;
  end.x = 400;
  end.y = 200;
  controller->drawer->drawLine(start, end);

  start.x = 200;
  start.y = 200;
  end.x = 200;
  end.y = 350;
  controller->drawer->drawLine(start, end);

  start.x = 200;
  start.y = 350;
  end.x = 400;
  end.y = 350;
  controller->drawer->drawLine(start, end);

  start.x = 400;
  start.y = 350;
  end.x = 400;
  end.y = 200;
  controller->drawer->drawLine(start, end);

  start.x = 200;
  start.y = 300;
  end.x = 280;
  end.y = 300;
  controller->drawer->drawLine(start, end);

  start.x = 300;
  start.y = 300;
  end.x = 300;
  end.y = 200;
  controller->drawer->drawLine(start, end);

  start.x = 300;
  start.y = 300;
  end.x = 380;
  end.y = 300;
  controller->drawer->drawLine(start, end);

  start.x = 250;
  start.y = 250;
  controller->drawer->drawText("305", start);

  start.x = 350;
  start.y = 250;
  controller->drawer->drawText("306", start);
}

void MainWindow::paintEvent(QPaintEvent *event) {
  Q_UNUSED(event);
  controller->drawer->painter = new QPainter(this);
  controller->drawer->painter->scale(controller->drawer->getScale(),
                                     controller->drawer->getScale());
  draw_example();
  controller->drawer->painter->end();
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