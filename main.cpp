#include "mainwindow.h"
#include <QApplication>

/*
 * for benchmarking
#include <iostream>
#include <chrono>

using namespace std;

 * from here my project related
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
*/

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow mainWindow;
    mainWindow.show();

    return app.exec();

    /*
     * for setting up for the benchmark test
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();

    auto start = std::chrono::system_clock::now();

    long long sum = 0;
    for (int i = 1; i <= 1000000; i++) {
        sum += i;
    }

    cout << "The sum is: " << sum << "\n";

    auto end = std::chrono::system_clock::now();

    // Benchmarking
    std::chrono::duration<double> diff = end - start;

    cout << "This took about: " << diff.count() << " seconds" << endl;

    return 0;
*/

/*
     * (commented out: giving flexibility to the greenPatch
     *
    QApplication app(argc, argv);

    // create a QGraphicsScene
    QGraphicsScene scene;

    // Create a QGraphics Rect Item with a green color
    QGraphicsRectItem * greenPatch = scene.addRect(0, 0, 100, 100, QPen(Qt::NoPen), QBrush(Qt::green));

    // Create a display
    QGraphicsView view(&scene);
    view.show();

    return app.exec();

*/
}
