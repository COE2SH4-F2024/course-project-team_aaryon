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
        if (i == 0){
            //This object insantiates once initially as the 10 point special object.
            objPos foodPos(5, i+3, 'c');
            foodBucket->insertHead(foodPos);
        }
        else if (i == (MAX_FOOD-1)){
            //This is the 50 point special object that increases length by 10.
            objPos foodPos(5, i+3, '0');
            foodBucket->insertHead(foodPos);
        }
        else{
            //This is the normal food object.
            objPos foodPos(5, i+3, 'o');
            foodBucket->insertHead(foodPos);
        }
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

        } while(randX == foodBucket->getElement(i).pos->x && randY == foodBucket->getElement(i).pos->y || repeat);

        // Depending on the loop iteration, add either a normal food object or one of the special ones
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
    // Returns a pointer to the foodBucket
    return foodBucket;
}

