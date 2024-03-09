#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "flower.h"
#include <QColor>
#include <QLineSeries>
#include <QChart>
#include <random>
#include <QImage>
#include <iostream>
#include <vector>
#include <QGraphicsScene>
#include <chrono>
#include <thread>

using namespace std;

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

random_device rd;     // Only used once to initialise (seed) engine
mt19937 rng(rd());    // Random-number engine used (Mersenne-Twister in this case)
uniform_int_distribution<int> uni_x(0, x_map - 1); // Guaranteed unbiased
uniform_int_distribution<int> uni_y(0, y_map - 1);


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

vector<int> flower_ids;
vector<flower> flowers;
uniform_int_distribution<int> uni_c(50, 100);

void MainWindow::setup_flowers(){
    flowers.clear();
    // Set the size of each flower
    int flowerSize = 5; // Adjust this value to change the size of the flowers
    int n_flowers = ui->spinBox_flowers->value();
    // Draw flowers randomly in the patch
    for (unsigned i = 0; i < n_flowers; i++)
    {
        flowers.emplace_back(std::vector<int>{}, true, 20, 0.1, i);  // create dummy flower object
        flowers[i].xy_cor = {uni_x(rng), uni_y(rng)};          // assign random x and y coordinates
        flowers[i].corolla_size = uni_c(rng);                   // update flower parameters
        flowers[i].id = i;                                        // assign flower id
        flower_ids.push_back(i);
        cout << '('<<flowers[i].xy_cor[0] <<','<< flowers[i].xy_cor[1] <<')'<< ", corolla size " << flowers[i].corolla_size << endl;
        cout <<','<< flowers[i].age <<')'<< ", corolla size " << flowers[i].corolla_size << endl;
        // add flower id to flower_ids vector
        // draw flowers

        //        int x = static_cast<int>(flowers[i].xy_cor[0]);
        //        int y = static_cast<int>(flowers[i].xy_cor[1]);

        for (int dx = -flowerSize; dx <= flowerSize; dx++) {
            for (int dy = -flowerSize; dy <= flowerSize; dy++) {
                // Check if the current pixel is within the circle
                if (dx * dx + dy * dy <= pow(flowerSize, 2)) {
                    // Set the color of the pixel to represent the flower
                    image.setPixel(flowers[i].xy_cor[0] + dx, flowers[i].xy_cor[1] + dy, qRgb(255* flowers[i].corolla_size /100, 0, 0)); // set pixel color
                }
            }
        }
//        scene->clear();
//        scene->addPixmap(QPixmap::fromImage(image));
    }
    scene->clear();
    scene->addPixmap(QPixmap::fromImage(image));
}


void MainWindow::on_start_clicked()
{
    update_map();
}


//      void simulateTime(std::vector<flower>& flowers) {

void MainWindow::update_map() {
    int iterationCount = 0;
    int maxIterations = 1000;

    while (iterationCount < maxIterations) {
        for (auto it = flowers.begin(); it != flowers.end(); ) {
            auto& flower = *it;

            // Simulate death
            if (flower.age > 100) {
                // Remove the dead flower from the vector
                it = flowers.erase(it);
            } else {
                // Update simulation or application state here

                // Increment age of the flower
                flower.age++;

                // Move on to the next flower
                ++it;
            }
        }

        // Add new flowers if needed (you can add your logic here)

        // Update the map with the current state of flowers
        update_map_image();

        // Increment the iteration counter
        iterationCount++;

        // Sleep if needed
        // this_thread::sleep_for(std::chrono::milliseconds(800)); // Sleep for 0.8 seconds
    }
}

void MainWindow::update_map_image() {
    // Clear the existing image
    image.fill(Qt::transparent);

    // Draw all the flowers onto the image
    for (const auto& flower : flowers) {
//        draw_flower(image, flower);
        draw_flower(image);
    }

    // Update the scene with the new image
    scene->clear();
    scene->addPixmap(QPixmap::fromImage(image));
}

//void MainWindow::draw_flower(QImage& image, const flower& flowers) {
void MainWindow::draw_flower(QImage& image) {
// Your code to draw a flower onto the image
    // Use the flower's position, size, etc., to draw it on the image
    for (const auto& flower : flowers) {
        // Redraw the flower if it's alive
        for (int dx = -flowerSize; dx <= flowerSize; dx++) {
            for (int dy = -flowerSize; dy <= flowerSize; dy++) {
                // Check if the current pixel is within the circle
                if (dx * dx + dy * dy <= pow(flowerSize, 2)) {
                    // Set the color of the pixel to represent the flower
                    image.setPixel(flower.xy_cor[0] + dx, flower.xy_cor[1] + dy, qRgb(255* flower.corolla_size /100, 0, 0)); // set pixel color
                }
            }
        }
    }
    // Update the scene with the new flower positions
    scene->addPixmap(QPixmap::fromImage(image));
}

//void MainWindow::update_map() {
//     int flowerSize = 5;
//        int maxIterations = 1000;

//        // ---------------------3------------------------
//        for (int iterationCount = 0; iterationCount < maxIterations; iterationCount++) {
//            // Iterate over the flowers vector
//            auto it = flowers.begin();
//            while (it != flowers.end()) {
//                // Simulate death
//                if (it->age > 100) {
//                    // Erase the flower from the vector if it's dead
//                    it = flowers.erase(it);
//                } else {
//                    // Increment the iterator if the flower is still alive
//                    ++it;
//                }
//            }

//            // Update the scene with the current state of the flowers
//            scene->clear();
//            for (const auto& flower : flowers) {
//                // Redraw the flower if it's alive
//                for (int dx = -flowerSize; dx <= flowerSize; dx++) {
//                    for (int dy = -flowerSize; dy <= flowerSize; dy++) {
//                        // Check if the current pixel is within the circle
//                        if (dx * dx + dy * dy <= pow(flowerSize, 2)) {
//                            // Set the color of the pixel to represent the flower
//                            image.setPixel(flower.xy_cor[0] + dx, flower.xy_cor[1] + dy, qRgb(255* flower.corolla_size /100, 0, 0)); // set pixel color
//                        }
//                    }
//                }
//            }
//            // Update the scene with the new flower positions
//            scene->addPixmap(QPixmap::fromImage(image));
//        }
//}

// -------------------------2----------------------
//    int maxIterations = 100;
//     int flowerSize = 5;
//        for (int iterationCount = 0; iterationCount < maxIterations; iterationCount++) {
//            for (auto it = flowers.begin(); it != flowers.end(); ) {
//                // Simulate death
//                if (it->age > 100) {
//                    // Remove the flower from the simulation
//                    it = flowers.erase(it);
//                } else {
//                    ++it;
//                }
//            }

//            // Update the scene with the current state of the flowers
//            scene->clear();
//            for (const auto& flower : flowers) {
//                if (flower.age <= 100) {
//                    // Redraw the flower if it's alive
//                    for (int dx = -flowerSize; dx <= flowerSize; dx++) {
//                        for (int dy = -flowerSize; dy <= flowerSize; dy++) {
//                            // Check if the current pixel is within the circle
//                            if (dx * dx + dy * dy <= pow(flowerSize, 2)) {
//                                // Set the color of the pixel to represent the flower
//                                image.setPixel(flower.xy_cor[0] + dx, flower.xy_cor[1] + dy, qRgb(255* flower.corolla_size /100, 0, 0)); // set pixel color
//                            }
//                        }
//                    }
//                }
//            }
//            // Update the scene with the new flower positions
//            scene->addPixmap(QPixmap::fromImage(image));
//        }

        /* --------------------------1---------------------
    int iterationCount = 0;
    int maxIterations = 1000;

    while (iterationCount < maxIterations) {

        for (auto& flower : flowers) {
//            for (int i = iterationCount; i < maxIterations; i++) {
                // Simulate death
                if (flower.age > 100) {
                    // Remove the flower from the simulation
                    // This could involve erasing it from the vector or marking it as inactive
                    flowers.erase(remove(flowers.begin(), flowers.end(), flower), flowers.end());
                }
            // Update simulation or application state here

            //+//
            //+// (@'o'@)##
            //+//
//            xy_cor_new = {uni_x(rng), uni_y(rng)};

//            corolla_size_new = uni_c(rng)
//            // to add an element at the end...
//            flowers.push_back(std::vector<int>{}, true, 20, 0.1, i);
//            // or, to add an element at the front...
//            flowers.insert(flowers.begin() + 0, std::vector<int>{}, true, 20, 0.1, i);
//            // Increment the iteration counter
            iterationCount++;

//            // Check if the desired number of iterations is reached

//            this_thread::sleep_for(std::chrono::milliseconds(800)); // Sleep for 0.8 seconds
        }
//            if (iterationCount >= maxIterations) {
//                break; // Exit the loop
        } */
//    }
