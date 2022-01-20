#include <iostream>
#include "shark.h"

using namespace std;

Shark::Shark() : Fish() , hunger(0.0) {
    SetEdible(false);
}

void Shark::Eat(vector<Fish*> fish_in_cell) {
    if (hunger <= 0.0) return;
    for (Fish* fptr : fish_in_cell) {
        if (fptr->IsAlive() && fptr->IsEdible()) {   // try to eat fish that are edible
            fptr->Die();
            hunger -= fptr->GetSize();
            if (hunger <= 0.0) {
                hunger = 0.0;
                return;
            }
        }
    }
}

void Shark::Grow() {
    if (hunger >= max_hunger) { // kill the shark if too hungry
        Die();
    }
    hunger += hunger_increment;
    Fish::Grow();
}

void Shark::Print() {
    cout << "Shark Hunger: " << hunger << " ";
    Fish::Print();
}


Fish* Shark::Reproduce() {
    Fish* fptr = Fish::Reproduce();        // try to have shark reproduce
    if (fptr == nullptr) return nullptr;
    delete fptr;
    return new Shark;
}
