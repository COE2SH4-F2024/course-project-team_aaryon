#include "Player.h"
#include <iostream>
using namespace std;

Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    playerPosList = new objPosArrayList();

    objPos headPos(mainGameMechsRef->getBoardSizeX()/2, mainGameMechsRef->getBoardSizeY()/2, '@');

    playerPosList->insertHead(headPos);

    // more actions to be included
    //playerPos.pos->x = mainGameMechsRef->getBoardSizeX()/2;
    //playerPos.pos->y = mainGameMechsRef->getBoardSizeY()/2;
    //playerPos.symbol = '@';
}


Player::~Player()
{
    // delete any heap members here
    // No keyword new
    delete playerPosList;

}

objPosArrayList* Player::getPlayerPos() const
{
    // return the reference to the playerPos array list
    return playerPosList;
}

void Player::updatePlayerDir()
{
    // PPA3 input processing logic
    char input = mainGameMechsRef->getInput();
    mainGameMechsRef->clearInput();
    switch(input) {
        case 'W':
        case 'w':
            if(myDir != UP && myDir != DOWN) {
                myDir = UP;
            }
            break;
        case 'S':
        case 's':
            if(myDir != UP && myDir != DOWN) {
                myDir = DOWN;
            }
            break;
        case 'A':
        case 'a':
            if(myDir != LEFT && myDir != RIGHT) {
                myDir = LEFT;
            }
            break;
        case 'D':
        case 'd':
            if(myDir != LEFT && myDir != RIGHT) {
                myDir = RIGHT;
            }
            break;
        case 32:
            myDir = STOP;
            break;
        case '.':
            mainGameMechsRef->setExitTrue();
            break;
    }
}

void Player::movePlayer()
{
    objPos tempPos = playerPosList->getHeadElement();

    switch (myDir)
    {
        // The below cases change either the x or y position depending on direction
        case UP:
            tempPos.pos->y--;
            break;
        case DOWN:
            tempPos.pos->y++;
            break;
        case LEFT:
            tempPos.pos->x--;
            break;
        case RIGHT:
            tempPos.pos->x++;
            break;
        default:
            break;
    }

    if(tempPos.pos->x <= 0) {
        tempPos.pos->x = mainGameMechsRef->getBoardSizeX()-2;
    } else if(tempPos.pos->x >= mainGameMechsRef->getBoardSizeX()-1) {
        tempPos.pos->x = 1;
    }

    if(tempPos.pos->y <= 0) {
        tempPos.pos->y = mainGameMechsRef->getBoardSizeY()-2;
    } else if (tempPos.pos->y >= mainGameMechsRef->getBoardSizeY()-1) {
        tempPos.pos->y = 1;
    }

    playerPosList->insertHead(tempPos);

    if(checkFoodConsumption()) {
            mainGameMechsRef->incrementScore();
            mainGameMechsRef->getFood()->generateFood(playerPosList, mainGameMechsRef->getBoardSizeX(), mainGameMechsRef->getBoardSizeY());
        } else {
            playerPosList->removeTail();
        }
    
    if(checkSelfCollision()) {
        mainGameMechsRef->setExitTrue();
        mainGameMechsRef->setLoseFlag();
    }
}
 

// More methods to be added
int Player::getDir() {
    return myDir;
}

bool Player::checkFoodConsumption() {
    for(int i=0; i<mainGameMechsRef->getFood()->getFoodPos()->getSize(); i++) {
        if(playerPosList->getHeadElement().pos->x == mainGameMechsRef->getFood()->getFoodPos()->getElement(i).pos->x && playerPosList->getHeadElement().pos->y == mainGameMechsRef->getFood()->getFoodPos()->getElement(i).pos->y) {
            return true;
        }
    }

    return false;
}

bool Player::checkSelfCollision() {
    for (int i = 1; i < playerPosList->getSize(); i++)
    {
        if(playerPosList->getHeadElement().pos->x == playerPosList->getElement(i).pos->x && playerPosList->getHeadElement().pos->y == playerPosList->getElement(i).pos->y) {
        return true;
        }
    }

    return false;
}