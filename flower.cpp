#include "flower.h"

//flower::flower()
//{
//}

flower::flower(
    std::vector<int> x_y_cor,
    bool sex, // T = male, F = female
    int corolla_size, // in mm
    double death_rate, // per year
    int id)
    : x_y_cor(x_y_cor), sex(sex), corolla_size(corolla_size), death_rate(death_rate), id(id)
{
    //    this -> x_y_cor;
    //    this -> sex;
    //    this -> corolla_size;
    //    this -> death_rate;
}
