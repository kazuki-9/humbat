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
        bool sex, // T = male, F = female
        int corolla_size, // in mm
        double death_rate, // per year
        int id
        );

    std::vector<int> xy_cor;
    bool sex; // T = male, F = female
    int corolla_size; // in mm
    double death_rate; // per year
    QRgb color;
    int id;
};

#endif // FLOWER_H


/*
In the constructor patch::patch, the lines this->patch_id;, this->xy_cor;, and this->N_seedlings; don't actually do anything meaningful. They are simply accessing the member variables of the class patch without assigning any values to them.

In C++, member variables are not automatically initialized to any specific value when an object is created. Therefore, the initial value of N_seedlings would be whatever garbage value happens to be in memory at the location where N_seedlings is stored.

To properly initialize the member variables in the constructor, you need to use the member initialization list:

patch::patch(std::string patch_id,
             std::vector<int> xy_cor,
             int N_seedlings)
    : patch_id(patch_id), xy_cor(xy_cor), N_seedlings(N_seedlings)
{
    // Constructor body (if needed)
}

*/
