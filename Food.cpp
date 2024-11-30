#include "Food.h"
#include <ctime>
#include <cstdlib>
#include <iostream>
using namespace std;

Food::Food() {
    // Creates a new arraylist to hold food items
    foodBucket = new objPosArrayList(5);
    // Creates 5 filler food items
    for(int i=0; i<MAX_FOOD; i++) {
        objPos foodPos(5, i+3, 'o');
        foodBucket->insertHead(foodPos);
    }
}

Food::~Food() {
    // Deletes the arraylist heap member
    delete foodBucket;
}

void Food::generateFood(objPosArrayList* blockOff, int xLim, int yLim) {
    srand(time(0)); // Seeds the random number generator
    for(int i=0; i<MAX_FOOD; i++) {
        int repeat, randX, randY;
        do {
            repeat = 0;
            randX = (rand() % (xLim-3)) + 1; // Creates a random number from [1, xRange-2]
            randY = (rand() % (yLim-3)) + 1; // Creates a random number from [1, yRange-2]
            for(int j=0; j<blockOff->getSize(); j++) {
                if(blockOff->getElement(j).pos->x == randX && blockOff->getElement(j).pos->y == randY) {
                    // If the coordinates match the position of any body of the snake, restart the generation
                    repeat = 1;
                }
            }

            for(int k=0; k<foodBucket->getSize(); k++) {
                if(randX == foodBucket->getElement(k).pos->x && randY == foodBucket->getElement(k).pos->y) {
                    // If the new food item matches the coordinates of a previous one, restart the generation
                    repeat = 1;
                }
            }
            // Stop this do-while loop once the new coordinates of the food item are different and the above if statmenents have passed

        } while(randX == foodBucket->getElement(i).pos->x && randY == foodBucket->getElement(i).pos->x && repeat);

        // Creates a new food item and inserts it into the list
        objPos foodPos(randX, randY, 'o');
        foodBucket->removeHead();
        foodBucket->insertTail(foodPos);
    }
}

objPosArrayList* Food::getFoodPos() const {
    // Returns a pointer to the foodBucket
    return foodBucket;
}