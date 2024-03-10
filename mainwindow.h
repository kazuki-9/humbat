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
    QLineSeries *series;
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

    void draw_chart();
};

#endif // MAINWINDOW_H
