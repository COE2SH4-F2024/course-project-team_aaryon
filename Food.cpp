#include "Food.h"
#include <ctime>
#include <cstdlib>

Food::Food() {
    foodPos.pos->x = 10;
    foodPos.pos->y = 10;
    foodPos.symbol = '^';
}

Food::~Food() {

}

void Food::generateFood(objPos blockOff, int xLim, int yLim) {
    srand(time(0));
    int repeat, randX, randY;
    do {
        repeat = 0;
        randX = (rand() % (xLim-3)) + 1; // Creates a random number from [1, xRange-2]
        randY = (rand() % (yLim-3)) + 1; // Creates a random number from [1, yRange-2]
        if(randX == blockOff.pos->x || randY == blockOff.pos->y) {
            repeat = 1;
        }
        
    } while(randX == foodPos.pos->x && randY == foodPos.pos->x || repeat);

    foodPos.pos->x = randX;
    foodPos.pos->y = randY;
}

objPos Food::getFoodPos() const {
    return foodPos;
}