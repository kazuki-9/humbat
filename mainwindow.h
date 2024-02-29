#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"
#include <QMainWindow>
#include <QtCharts>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow(); //@ Declaration of the destructor

//private:
//    Ui::MainWindow *ui;

private:
    Ui::MainWindow *ui;
    QLineSeries *series;
    QChart *chart;
};

#endif // MAINWINDOW_H
