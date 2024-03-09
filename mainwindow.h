#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "flower.h"
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

    int flowerSize = 5;

private slots:
    void on_setup_clicked();
    void on_start_clicked();

private:
    Ui::MainWindow *ui;

    // Parameters
    const unsigned x_map = 300;
    const unsigned y_map = 300;
    const unsigned n_flowers = 10;

    // QImage
    QImage image;
    std::vector<QRgb> color;
    QGraphicsScene *scene;

    // Functions
    void setup_map();
    void setup_flowers();
    void update_map();
//    void draw_flower(QImage& image, const flower& flowers);
    void draw_flower(QImage& image, const flower& f);
    void update_map_image();
};

#endif // MAINWINDOW_H
