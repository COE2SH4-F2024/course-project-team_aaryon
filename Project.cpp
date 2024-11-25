#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "Player.h"
#include "string.h"
#include "Food.h"
#include <windows.h>

using namespace std;

#define DELAY_CONST 100000

Player *myPlayer; // Global pointer meant to instatiate a player object on heap
GameMechs *myGM;
Food *snakeFood;

char dirList[5][6] = {"UP", "DOWN", "LEFT", "RIGHT", "STOP"};

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);

// Hides the Cursor
void HideCursor() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;

    if(GetConsoleCursorInfo(hConsole, &cursorInfo)) {
        cursorInfo.bVisible = FALSE;
        SetConsoleCursorInfo(hConsole, &cursorInfo);
    }
}

int main(void)
{

    Initialize();

    while(myGM->getExitFlagStatus() == false && myGM->getLoseFlagStatus() == false)  
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();

}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();

    myGM = new GameMechs();
    myPlayer = new Player(myGM);
    snakeFood = new Food();
    snakeFood->generateFood(myPlayer->getPlayerPos()->getHeadElement(), myGM->getBoardSizeX(), myGM->getBoardSizeY());

    HideCursor();
}

void GetInput(void)
{
    myGM->collectAsyncInput();
    char userInput = myGM->getInput(); 

    if (userInput != 0) { 
        myPlayer->updatePlayerDir(); 
    }

    //debugging keys

    if (userInput == '1'){
        myGM->incrementScore();
    }
    else if (userInput == '2'){
        myGM->setLoseFlag();
    } else if (userInput == '3') {
        snakeFood->generateFood(myPlayer->getPlayerPos()->getHeadElement(), myGM->getBoardSizeX(), myGM->getBoardSizeY());
    }
   
}

void RunLogic(void)
{
    myPlayer->movePlayer();
    myGM->clearInput();
}

void DrawScreen(void)
{
    MacUILib_clearScreen();

    objPos head = myPlayer->getPlayerPos()->getHeadElement();

    for(int y=0; y<myGM->getBoardSizeY(); y++) {
        for(int x=0; x<myGM->getBoardSizeX(); x++) {
            if(x == 0 || x == myGM->getBoardSizeX() - 1 || y == 0 || y == myGM->getBoardSizeY()-1) {
                MacUILib_printf("# ");
            } else if(x == head.pos->x && y == head.pos->y) {
                MacUILib_printf("%c ", head.getSymbol());
            } else if(x == snakeFood->getFoodPos().pos->x && y == snakeFood->getFoodPos().pos->y) {
                MacUILib_printf("%c ", snakeFood->getFoodPos().getSymbol());
            } else {
                MacUILib_printf("  ");
            }
        }
        MacUILib_printf("\n");
    }

    MacUILib_printf("%s\n", dirList[myPlayer->getDir()]);
    MacUILib_printf("Score: %d\n", myGM->getScore());
    if (myGM->getLoseFlagStatus() == true){
        MacUILib_printf("You Lose :(");
    } else if (myGM->getExitFlagStatus() == true) {
        MacUILib_printf("You ended the game.");
    }
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    //MacUILib_clearScreen(); Uncomment to clear the screen upon game end

    delete myPlayer;
    delete myGM;
    delete snakeFood;

    MacUILib_uninit();
}
