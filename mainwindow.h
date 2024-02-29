#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"
#include <QMainWindow>
#include <QFrame>
#include <QPainter>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow(); //@ Declaration of the destructor

//private:
//    Ui::MainWindow *ui;

private:
    QFrame *greenPatch;
    Ui::MainWindow *ui;

    /*
protected:
    void paintEvent(QPaintEvent *event) override {
        QMainWindow::paintEvent(event);

        QPainter painter(this);

        // Draw a flower
        painter.setBrush(Qt::red); // Set brush color to red for the petals
        painter.drawEllipse(50, 50, 20, 20); // Draw the petals
        painter.setBrush(Qt::yellow); // Set brush color to yellow for the center
        painter.drawEllipse(57, 57, 6, 6); // Draw the center of the flower
    }
*/
};

#endif // MAINWINDOW_H
