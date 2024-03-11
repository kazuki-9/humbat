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
#include <algorithm>

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
    setup_map(); // set up the map for the first time without any flowers
    setup_chart(); // set up the chart for the first time without any flowers

    uni_x = uniform_int_distribution<int> (flower_size, x_map -flower_size); // Randomly select the x coordinate
    uni_y = uniform_int_distribution<int> (flower_size, y_map -flower_size); // Randomly select the y coordinate
    uni_c = uniform_int_distribution<int> (min_corolla_size, max_corolla_size); // Randomly select the corolla size
    uni_d = uniform_int_distribution<int> (-3, 3); // Randomly select the direction of movement
    uni_c_change = uniform_int_distribution<int> (0, 1); // Randomly select the degree of change in corolla size
}

MainWindow::~MainWindow() {  delete ui; } // Destructor definition

void MainWindow::setup_chart() {    // Setting up the chart for plotting the corolla size change over generations
    chart = new QChart();
    series_1 = new QLineSeries();    
    chart->addSeries(series_1);
    chart->createDefaultAxes();
    chart->axisX()->setTitleText("Time [generations]");
    chart->axisY()->setTitleText("Corolla size [mm]");
    chart->setTitle("<H2>Flower evolution model</H2>");

    int x_min = 0;
    int x_max = 200; // plot only until 200 generations later
    int y_min = min_corolla_size;
    int y_max = max_corolla_size;
    // Set the range
    chart->axisX()->setRange(x_min, x_max);
    chart->axisY()->setRange(y_min, y_max);

    ui->my_chart->setChart(chart); // Set the chart to the view
}

random_device rd;     // Only used once to initialise (seed) engine
mt19937 rng(rd());   // random-number engine used (Mersenne-Twister in this case)

void MainWindow::setup_map() {
    scene = new QGraphicsScene;
    ui->map->setScene(scene);
    ui->map->resize(x_map, y_map); // resize the map
    image = QImage(x_map, y_map, QImage::Format_ARGB32); //@ Format_ARGB32 is a 32-bit RGB format
    image.fill(QColor(Qt::green).lighter(130)); // Adjust the alpha value to make it light green
    scene->addPixmap(QPixmap::fromImage(image));
}

void MainWindow::on_setup_clicked() {
    scene->clear();
    setup_map();    // Renew the map
    setup_flowers();// , with flowers
}

vector<flower> flowers;
void MainWindow::setup_flowers() { // Assign variables to flowers and draw them on the map
    //    scene->clear();
    flowers.clear();
    // Set the size of each flower
    unsigned n_flowers = ui->spinBox_flowers->value();
    // Draw flowers randomly in the patch
    for (unsigned i = 0; i < n_flowers; i++) {
        flowers.emplace_back(std::vector<int>{}, 0, 0, 0, i);  // variables are xy_cor, time_elapsed, generation, corolla_size, id
        flowers[i].xy_cor = {uni_x(rng), uni_y(rng)};          // assign random x and y coordinates
        flowers[i].corolla_size = uni_c(rng);                   // update flower parameters
        flowers[i].id = i + 1;                                        // assign flower id
        //        cout << '('<<flowers[i].xy_cor[0] <<','<< flowers[i].xy_cor[1] <<')'<< ", corolla size " << flowers[i].corolla_size << endl;

        // draw flowers
        for (int dx = -flower_size; dx <= flower_size; dx++) {
            for (int dy = -flower_size; dy <= flower_size; dy++) {
                // Check if the current pixel is within the circle
                if (dx * dx + dy * dy <= pow(flower_size, 2)) {
                    // Set the color of the pixel to represent the flower
                    image.setPixel(flowers[i].xy_cor[0] + dx, flowers[i].xy_cor[1] + dy, qRgb(255* flowers[i].corolla_size / max_corolla_size, 0, 0)); // set pixel color
                }
            }
        }
    }
    scene->addPixmap(QPixmap::fromImage(image));
}

void MainWindow::on_start_clicked() {
    ui->start->setEnabled(false);
    QCoreApplication::processEvents(); // make sure to update the UI
    update_map();
    unit_test();
    ui->start->setEnabled(true); 
}

void MainWindow::update_map() {
    // flower generation
    int max_iterations = 500; // number of iterations till stop
    for (int iteration_count = 0; iteration_count < max_iterations; ++iteration_count) {
        // Update the parameters of existing flowers
        for (auto& flower : flowers) {
            // Simulate aging
            flower.time_elapsed++;
            // Renew flower parameters if needed
            if (flower.time_elapsed % 100 == 0) { // after 100 steps, 1 generation increment
                flower.generation++;    // This reflect the death of old generation and birth of new generation, assuming all the flowers
                    // have a offspring near their original position, with other variables
                if (flower.corolla_size<= min(ui->spinBox_hums_range_max->value(), ui->spinBox_bats_range_min->value())) { // if the flower is within the range of hummingbirds
                    flower.corolla_size -= uni_c_change(rng); // decrease the corolla size
                } else if (flower.corolla_size > max(ui->spinBox_hums_range_max->value(), ui->spinBox_bats_range_min->value())){ // if the flower is within the range of bats
                    flower.corolla_size += uni_c_change(rng); // increase the corolla size
                } else if (flower.corolla_size > ui->spinBox_bats_range_min->value() && flower.corolla_size<= ui->spinBox_hums_range_max->value()) { // Competition between bats and hummingbirds
                    if (randomFloat_0_1(rng) > 0.5) { // 50% chance of increasing or decreasing the corolla size
                        flower.corolla_size += uni_c_change(rng);
                    } else {
                        flower.corolla_size -= uni_c_change(rng);
                    }
                }
                // Ensure corolla size is within the range
                if (flower.corolla_size < min_corolla_size) {
                    flower.corolla_size = min_corolla_size;
                } else if (flower.corolla_size > max_corolla_size) {
                    flower.corolla_size = max_corolla_size;
                }              
                // Simulate movement
                int new_x = flower.xy_cor[0] + uni_d(rng);
                int new_y = flower.xy_cor[1] + uni_d(rng);
                new_x = std::max(flower_size, std::min(new_x, x_map - flower_size - 1)); // Ensure the new coordinates stay within the map boundaries
                new_y = std::max(flower_size, std::min(new_y, y_map - flower_size - 1)); // Chat GPT
                flower.xy_cor = {new_x, new_y}; // Assign new n-y coordinates for move-appearance between generations
                // Fill the series with the new data
                series_1->setColor(QColor(255, flowers[0].id * 12, 0));
                series_1->setName("F " + QString::number(flowers[0].id));
                series_1->append(flowers[0].generation, flowers[0].corolla_size);
            }
        }
        update_map_image(); // Update the map with the current state of flowers
    }
    chart->addSeries(series_1);
}

void MainWindow::update_map_image() {
    scene->clear(); // Update the scene with the new image
    image.fill(QColor(Qt::green).lighter(130)); // Clear the existing image
    for (const auto& flower : flowers) { // Draw all the flowers onto the image
        draw_flower(image, flower);
    }
    scene->addPixmap(QPixmap::fromImage(image)); // Add the image to the scene
}

void MainWindow::draw_flower(QImage& image, const flower& flower) { // Re-draw the flower onto the image with the updated xy-coordinates
    for (const auto& flower : flowers) {
        // Redraw the flower for the next generations
        for (int dx = -flower_size; dx <= flower_size; dx++) {
            for (int dy = -flower_size; dy <= flower_size; dy++) {
                // Check if the current pixel is within the circle
                if (dx * dx + dy * dy <= pow(flower_size, 2)) {
                    // Set the color of the pixel to represent the flower
                    // The bigger the corolla size, the brighter red the color is.
                    image.setPixel(flower.xy_cor[0] + dx, flower.xy_cor[1] + dy, qRgb(255* flower.corolla_size / max_corolla_size, 0, 0));
                }
            }
        }
    }
}

bool MainWindow::unit_test() { // Unit test
    int result1 = flowers[0].corolla_size; // index [0], or any arbitrary flower
    if (result1 > max_corolla_size || result1 < min_corolla_size) {
        cout << "Unit test failed :(" << endl;
        return false;
    }
    cout << "Unit test cleared :)" << endl;
    return true;
}

// ------------scrap -------------------------------

//void MainWindow::calculate_average() {
//    int sum = 0;
////    for (const auto& flower : flowers) {
//        sum += flower.corolla_size;
////    }
//    int average = sum / flowers.size();
//    cout << "Average corolla size: " << average << endl;
//----------------------------------------------
//        calculate_average();
//                int sum = 0;
//                sum += flower.corolla_size;
//                //    }
//                int average = sum / n_flowers;
//            cout << "id " << flower.id <<", generation " << flower.generation <<", corolla size "<< flower.corolla_size << endl;
//        cout << "Average corolla size: " << average << endl;
//            series_2->append(flower.generation, average);



//    for (int timestep = 0; timestep < series_corolla_size.size(); timestep++) {
//        // Append data point to the series for the current time step
//        series_corolla_size->append(timestep, series_corolla_size[timestep]);
//    }


// ------------------------------------------------
//        std::vector<int> corollaSizeSnapshot;
//        for (const auto& flower : flowers) {
//            corollaSizeSnapshot.push_back(flower.corolla_size);
//        }

//        series_corolla_size.push_back(corollaSizeSnapshot);
// ------------------------------------------------
