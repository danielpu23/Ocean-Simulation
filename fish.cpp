#include <iostream>
#include <cstdlib>
#include "fish.h"

using namespace std;

Fish::Fish() {
    reproduce_probability = 0.8; // Initialized to 0.8
    growth_rate = 0.2; // Initialized to 0.2
    size = 1; // Initialized to 1
    age = 0; // Initialized to 0
    alive = true; // Initialized to true
    edible = true;
}

void Fish::Grow() {
    size += growth_rate * size;
    growth_rate *= 0.8; //increment size
    age++; // increment age
    if (age > 3) {       // 0.2 percent chance for fish to die naturally when age > 3
        int i = rand() % 1000;
        if (i < 200) alive = false;
    }
}

Fish* Fish::Reproduce() {
    float threshold = static_cast<float>(age - 2) * reproduce_probability * 1000.0; // reproduce with probability of age-2 * reproduce_probability
    float f = static_cast<float>(rand() % 1000);
    if (f < threshold) {
        return new Fish;   // successfully produce new fish
    } else {
        return nullptr;  // else return nullptr
    }
}

void Fish::Eat(std::vector<Fish*> fish_in_cell) {

}

bool Fish::IsAlive() {
    return alive;
}

// Print the vital stats of the fish.
void Fish::Print() {
    cout << "Age: " << age << " Size: " << size << endl;
}

void Fish::Die() {
    alive = false;
}

void Fish::SetEdible(bool e) {
    edible = e;
}

bool Fish::IsEdible() {
    return edible;
}

float Fish::GetSize() {
    return size;
}
