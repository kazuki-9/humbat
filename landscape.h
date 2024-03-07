#ifndef LANDSCAPE_H
#define LANDSCAPE_H
#include <random>
//#include <vector>

class landscape
{
public:
    landscape(const unsigned x_map, const unsigned y_map);
    landscape();

private:
std::mt19937 rng; // Random-number engine used (Mersenne-Twister in this case)

unsigned x_map = 0; //+ x_map again in this private section for the constructor(?)
unsigned y_map = 0;
};

#endif // LANDSCAPE_H
