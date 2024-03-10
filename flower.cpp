#include "flower.h"


//flower::flower()
//{
//}

flower::flower(
    std::vector<int> xy_cor,
    int age, // for renewing the variables
    int corolla_size, // in mm
//    double death_rate, // per year
    int id)
    : xy_cor(xy_cor), age(age), corolla_size(corolla_size), id(id)
//    , is_alive(true)

{
        this -> xy_cor = xy_cor;
        this -> age = age;
        this -> corolla_size = corolla_size;
//        this -> death_rate = death_rate;
}

bool flower::operator==(const flower& other) const {
        // Compare each member variable for equality
        return (this->xy_cor == other.xy_cor) &&
               (this->age == other.age) &&
               (this->corolla_size == other.corolla_size) &&
//               (this->death_rate == other.death_rate) &&
               (this->id == other.id);
}
