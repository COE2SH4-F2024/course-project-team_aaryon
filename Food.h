#ifndef FOOD_H
#define FOOD_H

#include "objPos.h"

class Food {
private:
    objPos foodPos;
public:
    Food();
    ~Food();

    void generateFood(objPos blockOff, int xLim, int yLim); // Generates a new food item while keeping track of the player
    objPos getFoodPos() const;
};

#endif