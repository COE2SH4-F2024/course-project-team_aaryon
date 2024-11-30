#include "GameMechs.h"
#include "MacUILib.h"

GameMechs::GameMechs()
{
    // Creates default variables for the gamemech object
    input = 0;
    exitFlag = false;
    loseFlag = false;
    score = 0;

    boardSizeX = 30;
    boardSizeY = 15;

    snakeFood = new Food();
}

GameMechs::GameMechs(int boardX, int boardY)
{
    // Allows custom board dimensions to be entered
    input = 0;
    exitFlag = false;
    loseFlag = false;
    score = 0;

    boardSizeX = boardX;
    boardSizeY = boardY;

    snakeFood = new Food();
}

// Deletes the snakeFood heap member
GameMechs::~GameMechs()
{
    delete snakeFood;
}

// Returns the variable to track whether or not to quit the game
bool GameMechs::getExitFlagStatus() const
{
    return exitFlag;
}

// Returns the variable used to keep track if the player has lot
bool GameMechs::getLoseFlagStatus() const
{
    return loseFlag;
}
    

// Returns the input member field
char GameMechs::getInput()
{
    return input;
}

// Returns the score member field
int GameMechs::getScore() const
{
    return score;
}

// Increments score by 1
void GameMechs::incrementScore()
{
    score++;
}

// Returns the boardsizeX member field
int GameMechs::getBoardSizeX() const
{
    return boardSizeX;
}

// Returns the boardsizeY member field
int GameMechs::getBoardSizeY() const
{
    return boardSizeY;
}


// Sets the exitFlag to true
void GameMechs::setExitTrue()
{
    exitFlag = true;
}

// Sets the loseFlag to true
void GameMechs::setLoseFlag()
{
    loseFlag = true;
}

// Sets the input member field to some char
void GameMechs::setInput(char this_input)
{
    input = this_input;
}

// Makes the input null
void GameMechs::clearInput()
{
    input = '\0';
}

// Collects async input from the user
void GameMechs::collectAsyncInput() {
    if(MacUILib_hasChar() != '\0') {
        input = MacUILib_getChar();
    }
}

// Returns a pointer to the snakeFood member field
Food* GameMechs::getFood() {
    return snakeFood;
}