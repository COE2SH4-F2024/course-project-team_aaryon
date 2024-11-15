#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "Player.h"

using namespace std;

#define DELAY_CONST 100000

Player *myPlayer; // Global pointer meant to instatiate a player object on heap
GameMechs *myGM;
objPos* grid;


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
    int size=(myGM->getBoardSizeX())*2 + (myGM->getBoardSizeY())*2 - 4;
    grid = new objPos[size];
    int count=0;
    for(int y=0; y<myGM->getBoardSizeY(); y++) {
        for(int x=0; x<myGM->getBoardSizeX(); x++) {
            if(x==0 || x==myGM->getBoardSizeX()-1 || y==0 || y==myGM->getBoardSizeY()-1) {
                grid[count].setObjPos(x, y, '#');
                count++;
            }
        }
    }
}

void GetInput(void)
{
   myPlayer->updatePlayerDir();
}

void RunLogic(void)
{
    
}

void DrawScreen(void)
{
    MacUILib_clearScreen();

    int count=0;
    for(int y=0; y<myGM->getBoardSizeY(); y++) {
        for(int x=0; x<myGM->getBoardSizeX(); x++) {
            if(x==grid[count].pos->x && y==grid[count].pos->y) {
                MacUILib_printf("%c ", grid[count].getSymbol());
                count++;
            } else {
                MacUILib_printf("  ");
            }
        }
        MacUILib_printf("\n");
    }
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();

    delete myPlayer;
    delete myGM;
    delete[] grid;    

    MacUILib_uninit();
}
