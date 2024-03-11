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

//const int x_map = 300;
//const int y_map = 300;
//int flower_size = 4;
// int y_map = y_map; // somehow this doesn't work and makes a super large number


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    // Set up the UI
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

void MainWindow::setup_chart() {
    // Setting up the chart for plotting
    chart = new QChart();

    series_1 = new QLineSeries();
//    series_2 = new QLineSeries();
//    series_3 = new QLineSeries();
//    series_4 = new QLineSeries();
//    series_5 = new QLineSeries();
//    series_6 = new QLineSeries();
//    series_7 = new QLineSeries();
//    series_8 = new QLineSeries();
//    series_10 = new QLineSeries();
//    series_11 = new QLineSeries();
//    series_12 = new QLineSeries();
//    series_13 = new QLineSeries();
//    series_14 = new QLineSeries();
//    series_15 = new QLineSeries();
//    series_16 = new QLineSeries();
//    series_17 = new QLineSeries();
//    series_18 = new QLineSeries();
//    series_19 = new QLineSeries();
//    series_20 = new QLineSeries();

//    series_1->setColor(QColor(255, 1* 12, 0)); // shade the color depending on the id
//    series_2->setColor(QColor(255, 2* 12, 0));
//    series_3->setColor(QColor(255, 3* 12, 0));
//    series_4->setColor(QColor(255, 4* 12, 0));
//    series_5->setColor(QColor(255, 5* 12, 0));
//    series_6->setColor(QColor(255, 6* 12, 0));
//    series_7->setColor(QColor(255, 7* 12, 0));
//    series_8->setColor(QColor(255, 8* 12, 0));
//    series_9->setColor(QColor(255, 9* 12, 0));
//    series_10->setColor(QColor(255, 10* 12, 0));
//    series_11->setColor(QColor(255, 11* 12, 0));
//    series_12->setColor(QColor(255, 12* 12, 0));
//    series_13->setColor(QColor(255, 13* 12, 0));
//    series_14->setColor(QColor(255, 14* 12, 0));
//    series_15->setColor(QColor(255, 15* 12, 0));
//    series_16->setColor(QColor(255, 16* 12, 0));
//    series_17->setColor(QColor(255, 17* 12, 0));
//    series_18->setColor(QColor(255, 18* 12, 0));
//    series_19->setColor(QColor(255, 19* 12, 0));
//    series_20->setColor(QColor(255, 20* 12, 0));

    chart->addSeries(series_1);
//    chart->addSeries(series_2);
//    chart->addSeries(series_3);
//    chart->addSeries(series_4);
//    chart->addSeries(series_5);
//    chart->addSeries(series_6);
//    chart->addSeries(series_7);
//    chart->addSeries(series_8);
//    chart->addSeries(series_9);
//    chart->addSeries(series_10);
//    chart->addSeries(series_11);
//    chart->addSeries(series_12);
//    chart->addSeries(series_13);
//    chart->addSeries(series_14);
//    chart->addSeries(series_15);
//    chart->addSeries(series_16);
//    chart->addSeries(series_17);
//    chart->addSeries(series_18);
//    chart->addSeries(series_19);
//    chart->addSeries(series_20);

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

    ui->my_chart->setChart(chart);
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


void MainWindow::on_setup_clicked()
{
     //  chart->removeAllSeries(); whyyyyyyyyyyyyyyyyyyyyyyyyyyy
    scene->clear();
    setup_map();    // Renew the map
    setup_flowers();// , with flowers

    // Clear the series before adding new data
//    series->clear();
//    setup_chart();
}

vector<flower> flowers;

void MainWindow::setup_flowers(){
    flowers.clear();
    // Set the size of each flower
    unsigned n_flowers = ui->spinBox_flowers->value();
    // Draw flowers randomly in the patch
    for (unsigned i = 0; i < n_flowers; i++)
    {
        flowers.emplace_back(std::vector<int>{}, 0, 0, 0, i);  // variables are xy_cor, time_elapsed, generation, corolla_size, id
        flowers[i].xy_cor = {uni_x(rng), uni_y(rng)};          // assign random x and y coordinates
        flowers[i].corolla_size = uni_c(rng);                   // update flower parameters
        flowers[i].id = i + 1;                                        // assign flower id
        //        cout << '('<<flowers[i].xy_cor[0] <<','<< flowers[i].xy_cor[1] <<')'<< ", corolla size " << flowers[i].corolla_size << endl;
        //        cout <<','<< flowers[i].age <<')'<< ", corolla size " << flowers[i].corolla_size << endl;

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
    scene->clear();
    scene->addPixmap(QPixmap::fromImage(image));
}

void MainWindow::on_start_clicked()
{
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
                flower.generation++;
                if (flower.corolla_size<= min(ui->spinBox_hums_range_max->value(), ui->spinBox_bats_range_min->value())) {
                    flower.corolla_size -= uni_c_change(rng);
                } else if (flower.corolla_size > max(ui->spinBox_hums_range_max->value(), ui->spinBox_bats_range_min->value())){
                    flower.corolla_size += uni_c_change(rng);
                } else if (flower.corolla_size > ui->spinBox_bats_range_min->value() && flower.corolla_size<= ui->spinBox_hums_range_max->value()) {
                    // Competition between bats and hummingbirds
                    if (randomFloat_0_1(rng) > 0.5) {
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

                // Ensure the new coordinates stay within the map boundaries
                new_x = std::max(flower_size, std::min(new_x, x_map - flower_size - 1)); //Chat GPT
                new_y = std::max(flower_size, std::min(new_y, y_map - flower_size - 1));

                flower.xy_cor = {new_x, new_y}; // Assign new n-y coordinates for move appearance

                // Fill the series with the new data
                series_1->setColor(QColor(255, flowers[0].id * 12, 0));
                series_1->setName("F " + QString::number(flowers[0].id));
                series_1->append(flowers[0].generation, flowers[0].corolla_size);

            }
            cout << "id " << flower.id <<", generation " << flower.generation <<", corolla size "<< flower.corolla_size << endl;

        // Update the map with the current state of flowers
        update_map_image();
        }
    }
    chart->addSeries(series_1);
}


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
}

void MainWindow::draw_flower(QImage& image, const flower& flower) {
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
//for (int iteration_count = 0; iteration_count < max_iterations; ++iteration_count) {
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


//void MainWindow::plotScaledImage() {
//    scene->clear();
//    scene->addPixmap(QPixmap::fromImage(image.scaled(ui->map->size())));
//}

//void MainWindow::update_map() {
//     int flower_size = 5;
//        int max_iterations = 1000;

//        // ---------------------3------------------------
//        for (int iteration_count = 0; iteration_count < max_iterations; iteration_count++) {
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
//    int max_iterations = 100;
//     int flower_size = 5;
//        for (int iteration_count = 0; iteration_count < max_iterations; iteration_count++) {
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
    int iteration_count = 0;
    int max_iterations = 1000;

    while (iteration_count < max_iterations) {

        for (auto& flower : flowers) {
//            for (int i = iteration_count; i < max_iterations; i++) {
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
            iteration_count++;

//            // Check if the desired number of iterations is reached

//            this_thread::sleep_for(std::chrono::milliseconds(800)); // Sleep for 0.8 seconds
        }
//            if (iteration_count >= max_iterations) {
//                break; // Exit the loop
        } */
//    }
