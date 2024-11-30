#include "Food.h"
#include <ctime>
#include <cstdlib>
#include <iostream>
using namespace std;

Food::Food() {
    foodBucket = new objPosArrayList();
    for(int i=0; i<MAX_FOOD; i++) {
        if (i == 0){
            objPos foodPos(5, i+3, 'c');
            foodBucket->insertHead(foodPos);
        }
        else if (i == (MAX_FOOD-1)){
            objPos foodPos(5, i+3, '0');
            foodBucket->insertHead(foodPos);
        }
        else{
            objPos foodPos(5, i+3, 'o');
            foodBucket->insertHead(foodPos);
        }
    }
}

Food::~Food() {
    delete foodBucket;
}

void Food::generateFood(objPosArrayList* blockOff, int xLim, int yLim) {
    srand(time(0));
    for(int i=0; i<MAX_FOOD; i++) {
        int repeat, randX, randY;
        do {
            repeat = 0;
            randX = (rand() % (xLim-3)) + 1; // Creates a random number from [1, xRange-2]
            randY = (rand() % (yLim-3)) + 1; // Creates a random number from [1, yRange-2]
            for(int j=0; j<blockOff->getSize(); j++) {
                if(blockOff->getElement(j).pos->x == randX && blockOff->getElement(j).pos->y == randY) {
                    repeat = 1;
                }
            }

            for(int k=0; k<foodBucket->getSize(); k++) {
                if(randX == foodBucket->getElement(k).pos->x && randY == foodBucket->getElement(k).pos->y) {
                    repeat = 1;
                }
            }

        } while(randX == foodBucket->getElement(i).pos->x && randY == foodBucket->getElement(i).pos->y || repeat);

        if (i == 0){
            objPos foodPos(randX, randY, 'c');
            foodBucket->removeHead();
            foodBucket->insertTail(foodPos);
        }
        else if (i == (MAX_FOOD-1)){
            objPos foodPos(randX, randY, '0');
            foodBucket->removeHead();
            foodBucket->insertTail(foodPos);
        }
        else{
            objPos foodPos(randX, randY, 'o');
            foodBucket->removeHead();
            foodBucket->insertTail(foodPos);
        }
    }
}

objPosArrayList* Food::getFoodPos() const {
    return foodBucket;
}

