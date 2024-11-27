#ifndef FOOD_H
#define FOOD_H

#define MAX_FOOD 5

#include "objPosArrayList.h"

class Food {
private:
    objPosArrayList* foodBucket;
public:
    Food();
    ~Food();

    void generateFood(objPosArrayList* blockOff, int xLim, int yLim); // Generates a new food item while keeping track of the player
    objPosArrayList* getFoodPos() const;
};

#endif