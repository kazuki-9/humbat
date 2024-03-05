#include "mainwindow.h"
#include "flower.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow mainWindow;
    mainWindow.show();
//    drawFlower(mainWindow.ui->patch, 100, 100); //@ Call the drawFlower function

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

    return 0;  // return 0 means the program ran successfully
*/

}
