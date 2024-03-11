// constructor (declarations and more:see below)
// variable declaration
// function declaration

#ifndef FLOWER_H
#define FLOWER_H

#include <vector>
#include <QImage>

class flower {
public:
    flower(
        std::vector<int> xy_cor,
        int time_elapsed, // for renewing the generation
        int generation, // for renewing the variables
        int corolla_size, // in mm^2
        int id
        );

    std::vector<int> xy_cor;
    int time_elapsed;
    int generation;
    int corolla_size;
    int id;
    QRgb color;

    bool operator==(const flower& other) const;

//private:
//    std::vector<int> xy_cor;
//    int age;
//    int corolla_size;
//    double death_rate;
//    int id;
};

#endif // FLOWER_H
