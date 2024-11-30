#include "GameMechs.h"
#include "MacUILib.h"
#include <iostream>

using namespace std;

GameMechs::GameMechs()
{
    input = 0;
    exitFlag = false;
    loseFlag = false;
    score = 0;

    boardSizeX = 30;
    boardSizeY = 15;
}

GameMechs::GameMechs(int boardX, int boardY)
{
    input = 0;
    exitFlag = false;
    loseFlag = false;
    score = 0;

    boardSizeX = boardX;
    boardSizeY = boardY;

    snakeFood = new Food();
}

// do you need a destructor?
GameMechs::~GameMechs()
{
    delete snakeFood;
}

bool GameMechs::getExitFlagStatus() const
{
    return exitFlag;
}

bool GameMechs::getLoseFlagStatus() const
{
    return loseFlag;
}
    

char GameMechs::getInput()
{
    return input;
}

int GameMechs::getScore() const
{
    return score;
}

void GameMechs::incrementScore()
{
    score++;
}

void GameMechs::incrementScore10()
{
    score+=10;
}

void GameMechs::incrementScore50()
{
    score+=50;
}

int GameMechs::getBoardSizeX() const
{
    return boardSizeX;
}

int GameMechs::getBoardSizeY() const
{
    return boardSizeY;
}


void GameMechs::setExitTrue()
{
    exitFlag = true;
}

void GameMechs::setLoseFlag()
{
    loseFlag = true;
}

void GameMechs::setInput(char this_input)
{
    input = this_input;
}

void GameMechs::clearInput()
{
    input = '\0';
}

// More methods should be added here
void GameMechs::collectAsyncInput() {
    if(MacUILib_hasChar() != '\0') {
        input = MacUILib_getChar();
    }

    if(input == '\e') {
        setExitTrue();
    }
}

Food* GameMechs::getFood() {
    return snakeFood;
}