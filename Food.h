#ifndef FOOD_H
#define FOOD_H

#include "objPosArrayList.h"

class Food {
private:
    objPos foodPos;
public:
    Food();
    ~Food();
    Food(const Food &food);
    Food& operator=(const Food &food);

    void generateFood(objPosArrayList* blockOff, int xLim, int yLim); // Generates a new food item while keeping track of the player
    objPos getFoodPos() const;
};

#endif