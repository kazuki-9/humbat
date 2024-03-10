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
#include <algorithm>

using namespace std;

const int x_map = 300;
const int y_map = 300;
int flower_size = 4;
// int y_map = y_map; // somehow this doesn't work and makes a super large number


bool test_add() {
    return true;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    // Initialize start time and maximum simulation time
    startTime = std::chrono::steady_clock::now();
    maxSimulationTimeInSeconds = 3; // Set the maximum simulation time to 60 seconds
    // Set up the UI
    ui->setupUi(this);
    setup_map();

     // Setting up the chart for plotting
    chart = new QChart();
    series = new QLineSeries();
    series->setColor(Qt::red); // default color: blue
    series->setName("Flowers");

   chart->addSeries(series);  // a chart can have more than one series

    chart->createDefaultAxes();

    chart->axisX()->setTitleText("Time [t]");
    chart->axisY()->setTitleText("Corolla size [mm]");
    chart->setTitle("<H2>Flower evolution model</H2>");


    ui->my_chart->setChart(chart);
}

bool MainWindow::stopConditionMet() {
    // Get the current time
    auto currentTime = std::chrono::steady_clock::now();

    // Calculate the elapsed time since the simulation started
    auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime).count();

    // Check if the elapsed time exceeds the maximum simulation time
    return (elapsedTime >= maxSimulationTimeInSeconds);
}

random_device rd;     // Only used once to initialise (seed) engine
mt19937 rng(rd());    // Random-number engine used (Mersenne-Twister in this case)
uniform_int_distribution<int> uni_x(flower_size, x_map -flower_size); // Guaranteed unbiased
uniform_int_distribution<int> uni_y(flower_size, y_map -flower_size);


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
uniform_int_distribution<int> uni_c(30, 100);

void MainWindow::setup_flowers(){
    flowers.clear();
    // Set the size of each flower
    int n_flowers = ui->spinBox_flowers->value();
    // Draw flowers randomly in the patch
    for (unsigned i = 0; i < n_flowers; i++)
    {
        flowers.emplace_back(std::vector<int>{}, 0, 20, i);  // variables are xy_cor, age, corolla_size, id
        flowers[i].xy_cor = {uni_x(rng), uni_y(rng)};          // assign random x and y coordinates
        flowers[i].corolla_size = uni_c(rng);                   // update flower parameters
        flowers[i].id = i + 1;                                        // assign flower id
        flower_ids.push_back(i);
        //        cout << '('<<flowers[i].xy_cor[0] <<','<< flowers[i].xy_cor[1] <<')'<< ", corolla size " << flowers[i].corolla_size << endl;
        //        cout <<','<< flowers[i].age <<')'<< ", corolla size " << flowers[i].corolla_size << endl;

        // add flower id to flower_ids vector
        // draw flowers

        //        int x = static_cast<int>(flowers[i].xy_cor[0]);
        //        int y = static_cast<int>(flowers[i].xy_cor[1]);

        for (int dx = -flower_size; dx <= flower_size; dx++) {
            for (int dy = -flower_size; dy <= flower_size; dy++) {
                // Check if the current pixel is within the circle
                if (dx * dx + dy * dy <= pow(flower_size, 2)) {
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
uniform_int_distribution<int> uni_d(-3, 3); // Randomly select the direction of movement
uniform_int_distribution<int> uni_c_change(0, 1); // Randomly select the degree of change in corolla size

std::uniform_real_distribution<float> randomFloat_0_1;

void MainWindow::update_map() {
    int maxIterations = 2000;
    for (int iterationCount = 0; iterationCount < maxIterations; ++iterationCount) {
        //    while (!stopConditionMet()) {
        //        // Check if the maximum simulation time has been reached
        //        auto currentTime = std::chrono::steady_clock::now();
        //        auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime).count();
        //        if (elapsedTime >= maxSimulationTimeInSeconds) {
        //            break; // Exit the loop if the maximum simulation time is reached
        //        }

        // Update the parameters of existing flowers
        for (auto& flower : flowers) {
            // Simulate aging
            flower.age++;
            // Renew flower parameters if needed
            if (flower.age > 100) {
                flower.age = 0;
                if (flower.corolla_size<= min(ui->spinBox_hums_range_max->value(), ui->spinBox_bats_range_min->value())) {
                    flower.corolla_size -= uni_c_change(rng);
                } else if (flower.corolla_size > max(ui->spinBox_hums_range_max->value(), ui->spinBox_bats_range_min->value())){
                    flower.corolla_size += uni_c_change(rng);
                } else if (flower.corolla_size > ui->spinBox_bats_range_min->value() && flower.corolla_size<= ui->spinBox_hums_range_max->value()) {

                    // Competition
                    if (randomFloat_0_1(rng) > 0.5) {
                        flower.corolla_size += uni_c_change(rng);
                    } else {
                        flower.corolla_size -= uni_c_change(rng);
                    }
                }
                // Ensure corolla size is within the range
                if (flower.corolla_size < 30) {
                    flower.corolla_size = 30;
                } else if (flower.corolla_size > 100) {
                    flower.corolla_size = 100;
                }

                // Simulate movement
                int new_x = flower.xy_cor[0] + uni_d(rng);
                int new_y = flower.xy_cor[1] + uni_d(rng);

                // Ensure the new coordinates stay within the map boundaries
                new_x = std::max(flower_size, std::min(new_x, x_map - flower_size - 1)); //Chat GPT
                new_y = std::max(flower_size, std::min(new_y, y_map - flower_size - 1));

                flower.xy_cor = {new_x, new_y};

            }
            cout << "id " << flower.id <<", age " << flower.age <<", corolla size "<< flower.corolla_size << endl;
        }
        // Update the map with the current state of flowers
        update_map_image();
        if (iterationCount % 100 == 0)
        {
            draw_chart();
        }
        //        if (stopConditionMet()) {
        //            break; // Exit the loop if the condition is met
        //        }
        // Sleep if needed
        //        std::this_thread::sleep_for(std::chrono::milliseconds(800)); // Sleep for 0.8 seconds
    }
}


std::vector<std::vector<int>> series_corolla_size;
void MainWindow::draw_chart() {

    int xMin = 0;
    int xMax = 2000;
    int yMin = 30;
    int yMax = 100;

    // Clear the series before adding new data
    series->clear();

    for (int i = 0 ; i < n_flowers; i++) {
        std::vector<int>& corolla_size_data = series_corolla_size[i];

        // Add corolla size data for each time step
        for (int timestep = 0; timestep < corolla_size_data.size(); timestep++) {
            int corolla_size = corolla_size_data[timestep];
            // Append data point to the series for the current time step
            series->append(timestep, corolla_size);
        }
        chart->axisX()->setRange(xMin, xMax); // xMin, xMax are just placeholders
        chart->axisY()->setRange(yMin, yMax); // yMin, yMax are just placeholders

        // series->clear(); // deletes all data points
        //    series->append(xMin, series_corolla_size); // adds a data point; xValue could be a time step and yValue the population size
    }
}

// ------------------------------------------------
//        std::vector<int> corollaSizeSnapshot;
//        for (const auto& flower : flowers) {
//            corollaSizeSnapshot.push_back(flower.corolla_size);
//        }

//        series_corolla_size.push_back(corollaSizeSnapshot);
// ------------------------------------------------

    //    // Create a chart
    //    QChart *chart = new QChart();
    //    chart->setTitle("Flower Corolla Size");
    //    chart->setAnimationOptions(QChart::SeriesAnimations);

    //    // Create a bar series
    //    QBarSeries *series = new QBarSeries();
    //    series->setLabelsVisible(true);

    //    // Create the categories
    //    QStringList categories;
    //    for (auto& flower : flowers) {
    //        categories << QString::number(flower.id);
    //    }

    //    // Create the data
    //    QBarSet *set = new QBarSet("Corolla Size");
    //    for (auto& flower : flowers) {
    //        *set << flower.corolla_size;
    //    }

    //    // Add the data to the series
    //    series->append(set);

    //    // Add the series to the chart
    //    chart->addSeries(series);

    //    // Set the categories on the horizontal axis
    //    QBarCategoryAxis *axis = new QBarCategoryAxis();
    //    axis->append(categories);
    //    chart->createDefaultAxes();
    //    chart->setAxisX(axis, series);

    //    // Create a chart view
    //    QChartView *chartView = new QChartView(chart);
    //    chartView->setRenderHint(QPainter::Antialiasing);

    //    // Set the chart view as the central widget
    //    ui->chart->setCentralWidget(chartView);


// -------------------- for death start -----------------------------------
//for (int iterationCount = 0; iterationCount < maxIterations; ++iterationCount) {
//        for (auto it = flowers.begin(); it != flowers.end(); ) {
//            auto& flower = *it;

//            // Simulate death
//            if (flower.age > 100) {
//                // Remove the dead flower from the vector
//                it = flowers.erase(it);
//            } else {
//                // Update simulation or application state here
//                // maybe add corolla_size change with age
////                flower.corolla_size = flower.corolla_size + 1 * corolla_opening_factor; // Increment corolla size of the flower with random factor

//                // Increment age of the flower
//                flower.age++;

//                // Move on to the next flower
//                ++it;
//            }
//        }
//        // Add new flowers if needed (you can add your logic here)

//        // Update the map with the current state of flowers
//        update_map_image();
//        // Increment the iteration counter

//        // Sleep if needed
//        // this_thread::sleep_for(std::chrono::milliseconds(800)); // Sleep for 0.8 seconds
//    }
//}
// --------------------for death end -----------------------------------

void MainWindow::update_map_image() {
    // Clear the existing image
    image.fill(QColor(Qt::green).lighter(130));

    // Draw all the flowers onto the image
    for (const auto& flower : flowers) {
        //        draw_flower(image, flower);
        draw_flower(image, flower);
    }

    // Update the scene with the new image
    scene->clear();
    scene->addPixmap(QPixmap::fromImage(image));
    //    plotScaledImage();
    //    QCoreApplication::processEvents();
}

//void MainWindow::draw_flower(QImage& image, const flower& flowers) {
void MainWindow::draw_flower(QImage& image, const flower& flower) {
    // draw a flower onto the image
    for (const auto& flower : flowers) {
        // Redraw the flower if it's alive
        for (int dx = -flower_size; dx <= flower_size; dx++) {
            for (int dy = -flower_size; dy <= flower_size; dy++) {
                // Check if the current pixel is within the circle
                if (dx * dx + dy * dy <= pow(flower_size, 2)) {
                    // Set the color of the pixel to represent the flower
                    image.setPixel(flower.xy_cor[0] + dx, flower.xy_cor[1] + dy, qRgb(255* flower.corolla_size /100, 0, 0)); // set pixel color. The bigger the corolla size, the brighter red the color
                }
            }
        }
    }
}

//void MainWindow::plotScaledImage() {
//    scene->clear();
//    scene->addPixmap(QPixmap::fromImage(image.scaled(ui->map->size())));
//}

//void MainWindow::update_map() {
//     int flower_size = 5;
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
//                for (int dx = -flower_size; dx <= flower_size; dx++) {
//                    for (int dy = -flower_size; dy <= flower_size; dy++) {
//                        // Check if the current pixel is within the circle
//                        if (dx * dx + dy * dy <= pow(flower_size, 2)) {
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
//     int flower_size = 5;
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
//                    for (int dx = -flower_size; dx <= flower_size; dx++) {
//                        for (int dy = -flower_size; dy <= flower_size; dy++) {
//                            // Check if the current pixel is within the circle
//                            if (dx * dx + dy * dy <= pow(flower_size, 2)) {
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
