#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"
#include <QMainWindow>
#include <QtCharts>
#include <QLineSeries>
#include <QChart>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr); // Declaration of the constructor

    ~MainWindow(); // Declaration of the destructor

    void paintEvent(QPaintEvent *event); // Declaration of the paintEvent function
//private:
//    Ui::MainWindow *ui;
    void  setupFlowers(); //?? should it be under private slots ?

private slots:
    void on_setup_flowers_clicked();

private:
    Ui::MainWindow *ui;
    QLineSeries *series;
    QChart *chart;
};

#endif // MAINWINDOW_H
