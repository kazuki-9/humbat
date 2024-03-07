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


// declaration (initialisation?)
//MainWindow::MainWindow (
//    const unsigned x_map,
//    const unsigned y_map)
//    : x_map(x_map), y_map(y_map) {

//    std::random_device rd;     // Only used once to initialise (seed) engine
//    std::mt19937 rng(rd());    // Random-number engine used (Mersenne-Twister in this case)
//    std::uniform_int_distribution<int> uni_x(0, x_map - 1); // Guaranteed unbiased
//    std::uniform_int_distribution<int> uni_y(0, y_map - 1);
//    }

const int x_map = 300;
const int y_map = 300;
// int y_map = y_map; // somehow this doesn't work and makes a super large number


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

std::random_device rd;     // Only used once to initialise (seed) engine
std::mt19937 rng(rd());    // Random-number engine used (Mersenne-Twister in this case)
std::uniform_int_distribution<int> uni_x(0, x_map - 1); // Guaranteed unbiased
std::uniform_int_distribution<int> uni_y(0, y_map - 1);

void MainWindow::paintEvent(QPaintEvent *event) {
    QMainWindow::paintEvent(event);

//    QPainter painter(this);
}

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
       scene->clear();
    setup_map();
    setup_flowers();
//    for (int i = 0; i < 10; ++i) {
//        std::cout  << uni_x(0, x_map - 1);
//    }

}

std::vector<flower> flowers;

void MainWindow::setup_flowers(){
/// something like dispersing flowers randomly in the patch with the user-defined # of flowers
//    flowers.clear();

//    for (unsigned i = 0; i < n_flowers; i++) {
//        image.setPixelColor(uni_x(rng), uni_y(rng), Qt::red); // Randomly set the pixel color to yellow
//    }
    // Set the size of each flower
    int flowerSize = 5; // Adjust this value to change the size of the flowers

    // Draw flowers randomly in the patch
    for (unsigned i = 0; i < n_flowers; i++) {
        int x = uni_x(rng); // Get random x coordinate
        int y = uni_y(rng); // Get random y coordinate

        // Draw a circle for each flower
        for (int dx = -flowerSize; dx <= flowerSize; dx++) {
            for (int dy = -flowerSize; dy <= flowerSize; dy++) {
                // Check if the current pixel is within the circle
                if (dx * dx + dy * dy <= flowerSize * flowerSize) {
                    // Set the color of the pixel to represent the flower
                    image.setPixelColor(x + dx, y + dy, Qt::red);
                }
            }
        }
    }
    scene->clear();
    scene->addPixmap(QPixmap::fromImage(image));
}

