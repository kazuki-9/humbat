#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "flower.h"
#include "qlineseries.h"
#include "ui_mainwindow.h"
#include <QGraphicsScene>
#include <QMainWindow>

//#include <QtCharts>
//#include <QLineSeries>
//#include <QChart>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr); // Declaration of the constructor
    ~MainWindow(); // Declaration of the destructor

    int flower_size = 4;

private slots:
    void on_setup_clicked();
    void on_start_clicked();

private:
    Ui::MainWindow *ui;
    std::vector<QLineSeries*> series_list;
    QChart *chart;

    // Parameters
    const int x_map = 300;
    const int y_map = 300;
    const unsigned n_flowers = 10;
    std::chrono::steady_clock::time_point startTime;
    int maxSimulationTimeInSeconds; // Maximum simulation time in seconds

    // QImage
    QImage image;
    std::vector<QRgb> color;
    QGraphicsScene *scene;

    // Functions
    void setup_map();
    void setup_flowers();
    void update_map();
    void draw_flower(QImage& image, const flower& f);
    void update_map_image();
    bool stopConditionMet();
    void plotScaledImage();

    void setup_chart();
    void make_series();
    void draw_chart();
};

#endif // MAINWINDOW_H

/* **************************
 * *** About this program ***
 * **************************
 *
 * Author: Kazuki Uchino
 * Matriculation number: 29225754
 *
 * *** RESEARCH QUESTION: ***
 *
 * Will flowers evolve in a way so that they will prefer bats (or hummingbirds) as their pollinators?
 *
 * *** BACKGROUND INFORMATION: ***
 *
 *  Hummingbirds are known to fly around to get nectar from nectarious plants while they unintentionally pollinate the plants.
 *  Some bat species in Mexico are also known to feed on nectar in night time, through which, again, they pollinate the plants.
 *  A research from Muchhala (2007) shows that while hummingbirds forage for narrower flowers and are less efficient in pollination,
 *  bats forage for wider flowers and are more efficient in pollination. Due to the higher feedback on plants' pollen production,
 *  a model shows that the plants' evolutionary shifts from bird to bat pollination (Muchhala and Thomson, 2010).
 *  # References:
 *  -	Muchhala, Nathan (2007): Adaptive trade-off in floral morphology mediates specialization for flowers pollinated by bats and hummingbirds. In The American Naturalist 169 (4), pp. 494–504. DOI: 10.1086/512047.
 *  -	Muchhala, Nathan; Thomson, James D. (2010): Fur versus feathers: pollen delivery by bats and hummingbirds and consequences for pollen production. In The American Naturalist 175 (6), pp. 717–726. DOI: 10.1086/652473.
 *
 *  ABOUT THIS PROGRAM: ***
 *
 *  The program simulates the process of pollination by hummingbirds and bats.
 *  How to use the program: the user can set up the parameters for the simulation, such as the number of flowers and the target
 *  corolla size of hummingbirds and bats for the flowers. The output of the program is a graphical representation of the number
 *  of flowers with different corolla size over generations.
 *  The research suggests that there are no competition between the two pollinators for flowers with intermediate corolla size, and
 *  but the user can also simulate such competition.
 *  An enhanced version of the program may include functionalities such as moving the pollinators and their behaviours (e.g. bats
 *  eat pollens during the pollination process). Other functions such as pollen productivity of flowers and fitness of pollinators
 *  could also complement the program well.
 *
 *  *** SOURCES: ***
 *
 *  Variables of flower are specified in the flower.h file.
 *  Almost everyting is in the mainwindow.cpp file.
 *
 */
