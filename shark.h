#ifndef SHARK_H_INCLUDED
#define SHARK_H_INCLUDED

#include <vector>
#include "fish.h"

using namespace std;

// Shark class that inherits from Fish

class Shark : public Fish {
public:
    Shark();
    void Grow();
    void Print();
    Fish* Reproduce();
    void Eat(std::vector<Fish*> fish_in_cell);
private:
    static const float max_hunger;
    static float hunger_increment;
    float hunger;
};


#endif // SHARK_H_INCLUDED
