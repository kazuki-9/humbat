// mainwindow.cpp

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "flower.h"
#include <QColor>
//#include <QFrame>
//#include <QPainter>
#include <QLineSeries>
#include <QChart>
#include <random>
#include <QImage>
#include <iostream>


// declaration
//MainWindow::MainWindow (
//    const unsigned x_map,
//    const unsigned y_map)
//    {
//    }

int x_map = 100;
int y_map = 100;
// int y_map = y_map; // somehow this doesn't work and makes a super large number

std::random_device rd;     // Only used once to initialise (seed) engine
std::mt19937 rng(rd());    // Random-number engine used (Mersenne-Twister in this case)
std::uniform_int_distribution<int> uni_x(0, x_map - 1); // Guaranteed unbiased
std::uniform_int_distribution<int> uni_y(0, y_map - 1);


bool test_add() {
    return true;
}

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
//    for (int i = 0; i < 10; ++i) {
//        std::cout  << uni_x(0, x_map - 1);
//    }
}

std::vector<flower> flowers;

void MainWindow::setup_flowers(){
/// something like dispersing flowers randomly in the patch with the user-defined # of flowers
    flowers.clear();
    for (unsigned i = 0; i < n_flowers; i++) {
        image.setPixelColor(uni_x(rng), uni_y(rng), Qt::yellow); // Randomly set the pixel color to yellow
    }
    scene->addPixmap(QPixmap::fromImage(image));
}

