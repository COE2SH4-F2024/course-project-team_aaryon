#include "Player.h"

Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // more actions to be included
    playerPos.pos->x = mainGameMechsRef->getBoardSizeX()/2;
    playerPos.pos->y = mainGameMechsRef->getBoardSizeY()/2;
    playerPos.symbol = '@';
}


Player::~Player()
{
    // delete any heap members here
    // No keyword new
}

objPos Player::getPlayerPos() const
{
    // return the reference to the playerPos arrray list
    return playerPos;
}

void Player::updatePlayerDir()
{
    // PPA3 input processing logic
    switch(mainGameMechsRef->getInput()) {
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
        case '.':
            mainGameMechsRef->setExitTrue();
            break;
    }
}

void Player::movePlayer()
{
    // PPA3 Finite State Machine logic
}

// More methods to be added
int Player::getDir() {
    return myDir;
}