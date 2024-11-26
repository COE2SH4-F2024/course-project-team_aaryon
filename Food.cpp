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

void Food::generateFood(objPosArrayList* blockOff, int xLim, int yLim) {
    srand(time(0));
    int repeat, randX, randY;
    do {
        repeat = 0;
        randX = (rand() % (xLim-3)) + 1; // Creates a random number from [1, xRange-2]
        randY = (rand() % (yLim-3)) + 1; // Creates a random number from [1, yRange-2]
        for(int i=0; i<blockOff->getSize(); i++) {
            if(blockOff->getElement(i).pos->x == randX && blockOff->getElement(i).pos->y == randY) {
                repeat = 1;
            }
        }
        
    } while(randX == foodPos.pos->x && randY == foodPos.pos->x || repeat);

    foodPos.pos->x = randX;
    foodPos.pos->y = randY;
}

objPos Food::getFoodPos() const {
    return foodPos;
}

Food::Food(const Food &food) {
    foodPos.pos->x = food.foodPos.pos->x;
    foodPos.pos->y = food.foodPos.pos->y;
    foodPos.symbol = food.foodPos.getSymbol();
}

Food &Food::operator=(const Food &food) {
    foodPos.pos->x = food.foodPos.pos->x;
    foodPos.pos->y = food.foodPos.pos->y;
    foodPos.symbol = food.foodPos.getSymbol();

    return *this;
}