// mainwindow.cpp

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "flower.h"
#include <QColor>
//#include <QFrame>
//#include <QPainter>
#include <QLineSeries>
#include <QChart>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    // Set up the UI
    ui->setupUi(this);
    setup_map();
}

void MainWindow::paintEvent(QPaintEvent *event) {
    QMainWindow::paintEvent(event);

    QPainter painter(this); // Create a QPainter object
    //    painter.begin(this); //@ this didn't really improve anything
//    int x = 50;
//    int y = 50;
//    flower::drawFlower(&painter, x, y); // Call the drawFlower function
//    //    painter.end();
}

// flower::drawFlower(painter, x, y); // Call the drawFlower function

MainWindow::~MainWindow() {  delete ui; } // Destructor definition

void MainWindow::setup_map() {
    scene = new QGraphicsScene;
    ui->map->setScene(scene);
    ui->map->resize(x_map, y_map); // resize the map

    image = QImage(x_map, y_map, QImage::Format_ARGB32); //@ Format_ARGB32 is a 32-bit RGB format
    image.fill(QColor(Qt::green).lighter(130)); // Adjust the alpha value to make it lighter

    scene->addPixmap(QPixmap::fromImage(image));
}


void MainWindow::on_setup_clicked()
{
    setup_flowers();
}



void MainWindow::setup_flowers(){


    scene->addPixmap(QPixmap::fromImage(image));
}

