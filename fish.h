#ifndef FISH_H_INCLUDED
#define FISH_H_INCLUDED

#include <vector>

class Fish {
public:
    Fish();

    virtual void Grow();
    virtual void Print();
    virtual Fish* Reproduce();
    virtual void Eat(std::vector<Fish*> fish_in_cell);

    bool IsAlive();
    void Die();
    bool IsEdible();
    void SetEdible(bool e);
    float GetSize();

private:
    float reproduce_probability; // Initialized to 0.4
    float growth_rate; // Initialized to 0.2
    float size; // Initialized to 1
    int age; // Initialized to 0
    bool alive; // Initialized to true
    bool edible; // Initialized to true
};

#endif // FISH_H_INCLUDED
