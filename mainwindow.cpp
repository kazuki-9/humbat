// mainwindow.cpp

#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include <QFrame>
//#include <QPainter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    // Set up the UI
    ui->setupUi(this);

    // create the green patch
//    ui->patch->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    //  ui->patch->setStyleSheet("QFrame {background-color: yellowGreen }");

    QChartView *chartView = ui->patch; // Get the QChartView from the UI
    QChart *chart = chartView->chart(); // Get the chart associated with the QChartView
    chart->setBackgroundBrush(QBrush(QColorConstants::Svg::yellowgreen)); // Set the desired background color

//    QFrame *greenPatch = new QFrame(this);
//    greenPatch -> setStyleSheet("background-color: yellowGreen;");
//    greenPatch -> setFixedSize(600, 600);
//    greenPatch -> move(180, 50);
//    greenPatch -> show();
}

MainWindow::~MainWindow()
{
    delete ui;
} // Destructor definition

