#include "flower.h"


//flower::flower()
//{
//}

flower::flower(
    std::vector<int> xy_cor,
    int time_elapsed,
    int generation,
    int corolla_size, // in mm
    int id)
    : xy_cor(xy_cor), time_elapsed(time_elapsed), generation(generation), corolla_size(corolla_size), id(id)

{
        this -> xy_cor = xy_cor;
        this -> time_elapsed = time_elapsed;
        this -> generation = generation;
        this -> corolla_size = corolla_size;
}

bool flower::operator==(const flower& other) const {
        // Compare each member variable for equality
        return (this->xy_cor == other.xy_cor) &&
               (this->time_elapsed == other.time_elapsed) &&
               (this->generation == other.generation) &&
               (this->corolla_size == other.corolla_size) &&
               (this->id == other.id);
}
