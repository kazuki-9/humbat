#include "flower.h"

//flower::flower()
//{
//}

flower::flower(
    std::vector<int> xy_cor,
    bool sex, // T = male, F = female
    int corolla_size, // in mm
    double death_rate, // per year
    int id)
    : xy_cor(xy_cor), sex(sex), corolla_size(corolla_size), death_rate(death_rate), id(id)
{
        this -> xy_cor = xy_cor;
        this -> sex = sex;
        this -> corolla_size = corolla_size;
        this -> death_rate = death_rate;
}
