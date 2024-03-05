// mainwindow.cpp

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "flower.h"
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
}

void MainWindow::paintEvent(QPaintEvent *event) {
    QMainWindow::paintEvent(event);

    QPainter painter(this); // Create a QPainter object
    //    painter.begin(this); //@ this didn't really improve anything
    int x = 50;
    int y = 50;
    flower::drawFlower(&painter, x, y); // Call the drawFlower function
    //    painter.end();
}

// flower::drawFlower(painter, x, y); // Call the drawFlower function

MainWindow::~MainWindow()
{
    delete ui;
} // Destructor definition


void MainWindow::on_setup_flowers_clicked()
{
    setupFlowers();
}

void MainWindow::setupFlowers(){

    // Create a new series
    series = new QLineSeries();

    // Add data to the series
    series->append(0, 6);
    series->append(2, 4);
    series->append(3, 8);
    series->append(7, 4);
    series->append(10, 5);
    series->append(11, 1);
    series->append(13, 3);
    series->append(17, 6);
    series->append(18, 3);
    series->append(20, 2);

    // Create a new chart
    chart = new QChart();

    // Add the series to the chart
    chart->addSeries(series);

    // Set the title of the chart
    chart->setTitle("Simple line chart example");

    // Create a new chart view
    QChartView *chartView = new QChartView(chart);

    // Set the chart view to the chart
    chartView->setChart(chart);

    // Set the chart view to the main window
    setCentralWidget(chartView);
}
