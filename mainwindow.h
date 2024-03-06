#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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

    void paintEvent(QPaintEvent *event); // Declaration of the paintEvent function



private slots:
    void on_setup_clicked();


private:
    Ui::MainWindow *ui;

    // Parameters
    const unsigned x_map = 100;
    const unsigned y_map = 100;
    const unsigned n_flowers = 10;


    // QImage
    QImage image;
    std::vector<QRgb> color;
    QGraphicsScene *scene;

    // Functions
    void setup_map();
    void setup_flowers();
    //   void updateMaps();  //@ not yet constructed but maybe useful later

};

#endif // MAINWINDOW_H
