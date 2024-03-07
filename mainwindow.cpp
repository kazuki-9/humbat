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
}

//std::vector<flower> flowers;

std::vector<int> flower_ids;
std::vector<flower> flowers;
std::uniform_int_distribution<int> uni_c(50, 100);

void MainWindow::setup_flowers(){
    // Set the size of each flower
    int flowerSize = 5; // Adjust this value to change the size of the flowers
    int n_flowers = ui->spinBox_flowers->value();
    // Draw flowers randomly in the patch
    for (unsigned i = 0; i < n_flowers; i++)
//    {
//        int x = uni_x(rng); // Get random x coordinate
//        int y = uni_y(rng); // Get random y coordinate

//        // Draw a circle for each flower
//        for (int dx = -flowerSize; dx <= flowerSize; dx++) {
//            for (int dy = -flowerSize; dy <= flowerSize; dy++) {
//                // Check if the current pixel is within the circle
//                if (dx * dx + dy * dy <= flowerSize * flowerSize) {
//                    // Set the color of the pixel to represent the flower
//                    const QColor color(255* corolla_size, 0, 0);
//                    image.setPixelColor(x + dx, y + dy, color);
//                }
//            }
//        }
//    }

    {
        flowers.emplace_back(std::vector<int>{}, true, 20, 0.1, i);  // create dummy flower object
        flowers[i].x_y_cor = {uni_x(rng), uni_y(rng)};          // assign random x and y coordinates
//        if (i < N_birch_flowers){                                 // assign birch based on species_ratio
            flowers[i].corolla_size = uni_c(rng);                   // update species parameters
            image.setPixel(flowers[i].x_y_cor[0], flowers[i].x_y_cor[1], flowers[i].color); // set pixel color
//        } else {                                                // rest is oak
//            flowers[i].species = 'o';
//            flowers[i].update_species_params();
//            image.setPixel(flowers[i].x_y_cor[0], flowers[i].x_y_cor[1], flowers[i].color);
//        }
        flowers[i].id = i;                                        // assign flower id
        flower_ids.push_back(i);                                  // add flower id to flower_ids vector
    }
    scene->clear();
    scene->addPixmap(QPixmap::fromImage(image));
}


void MainWindow::on_start_clicked()
{
    update_map();
}

void MainWindow::update_map() {
    for (unsigned x = 0; x < x_map; x++) {
        for (unsigned y = 0; y < y_map; y++) {
//            if (
//                landscape.cowsMap[x][y]) {
            int corolla_size = flowers.corolla_size;
                image.setPixelColor(x, y, Qt::red);
//            } else {
                int corolla_size = flowers.corolla_size;
                const QColor color(255* corolla_size / 100, 0, 0); // if max = 100 mm
                image.setPixelColor(x, y, color);
//            }
        }
    }
}

