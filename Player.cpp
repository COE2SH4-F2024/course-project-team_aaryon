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
    switch (myDir)
    {
        // The below cases change either the x or y position depending on direction
        case UP:
            playerPos.pos->y--;
            break;
        case DOWN:
            playerPos.pos->y++;
            break;
        case LEFT:
            playerPos.pos->x--;
            break;
        case RIGHT:
            playerPos.pos->x++;
            break;
        default:
            break;
    }

    if(playerPos.pos->x <= 0) {
        playerPos.pos->x = mainGameMechsRef->getBoardSizeX()-2;
    } else if(playerPos.pos->x >= mainGameMechsRef->getBoardSizeX()-1) {
        playerPos.pos->x = 1;
    }

    if(playerPos.pos->y <= 0) {
        playerPos.pos->y = mainGameMechsRef->getBoardSizeY()-2;
    } else if (playerPos.pos->y >= mainGameMechsRef->getBoardSizeY()-1) {
        playerPos.pos->y = 1;
    }
}

// More methods to be added
int Player::getDir() {
    return myDir;
}