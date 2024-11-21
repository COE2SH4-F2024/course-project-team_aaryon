#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "Player.h"
#include "string.h"

using namespace std;

#define DELAY_CONST 100000

Player *myPlayer; // Global pointer meant to instatiate a player object on heap
GameMechs *myGM;

char dirList[5][6] = {"UP", "DOWN", "LEFT", "RIGHT", "STOP"};

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);

int main(void)
{

    Initialize();

    while(myGM->getExitFlagStatus() == false)  
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
}

void GetInput(void)
{
    char userInput = myGM->getInput(); 

    if (userInput != 0) { 
        myGM->setInput(userInput); 
        myPlayer->updatePlayerDir(); 
    }

    
    //debugging keys

    if (userInput == '1'){
        myGM->incrementScore();
    }
    else  if (userInput == '2'){
        myGM->setLoseFlag();
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

    for(int y=0; y<myGM->getBoardSizeY(); y++) {
        for(int x=0; x<myGM->getBoardSizeX(); x++) {
            if(x == 0 || x == myGM->getBoardSizeX() - 1 || y == 0 || y == myGM->getBoardSizeY()-1) {
                MacUILib_printf("# ");
            } else if(x == myPlayer->getPlayerPos().pos->x && y == myPlayer->getPlayerPos().pos->y) {
                MacUILib_printf("%c ", myPlayer->getPlayerPos().getSymbol());
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

    MacUILib_uninit();
}
