#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "Player.h"
#include "string.h"
#include "Food.h"
#include <windows.h>

using namespace std;

#define DELAY_CONST 100000

Player *myPlayer;
GameMechs *myGM;

// Used to print the state string for debugging
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

    myGM = new GameMechs(30, 15);
    myPlayer = new Player(myGM);
    myGM->getFood()->generateFood(myPlayer->getPlayerPos(), myGM->getBoardSizeX(), myGM->getBoardSizeY());

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

    // if (userInput == '1'){
    //     myGM->incrementScore();
    // }
    // else if (userInput == '2'){
    //     myGM->setLoseFlag();
    // } else if (userInput == '3') {
    //     myGM->getFood()->generateFood(myPlayer->getPlayerPos(), myGM->getBoardSizeX(), myGM->getBoardSizeY());
    // }
   
}

void RunLogic(void)
{
    myPlayer->movePlayer();
    myGM->clearInput();
}

void DrawScreen(void)
{
    MacUILib_clearScreen();
    bool drawSnakeBody, drawFood;

    // Loop to print the game board
    for(int y=0; y<myGM->getBoardSizeY(); y++) {
        for(int x=0; x<myGM->getBoardSizeX(); x++) {
            drawSnakeBody = false;
            drawFood = false;

            // Print out the snake body
            for(int i=0; i<myPlayer->getPlayerPos()->getSize(); i++) {
                objPos tempPos = myPlayer->getPlayerPos()->getElement(i);
                if(tempPos.pos->x == x && tempPos.pos->y == y) {
                    MacUILib_printf("%c ", tempPos.getSymbol());
                    drawSnakeBody = true;
                    break;
                }
            }

            // Once a body gets printed move on to the next coordinate
            if(drawSnakeBody) {
                continue;
            }

            // Loop to print out all the foods
            for(int i=0; i<myGM->getFood()->getFoodPos()->getSize(); i++) {
                if(x == myGM->getFood()->getFoodPos()->getElement(i).pos->x && y == myGM->getFood()->getFoodPos()->getElement(i).pos->y) {
                    MacUILib_printf("%c ", myGM->getFood()->getFoodPos()->getElement(i).getSymbol());
                    drawFood = true;
                    break;
                }
            }

            // Once a food item gets printed move on to the next coordinate
            if(drawFood) {
                continue;
            }


            // Prints the border
            if(x == 0 || x == myGM->getBoardSizeX() - 1 || y == 0 || y == myGM->getBoardSizeY()-1) {
                MacUILib_printf("# ");
            } else {
                MacUILib_printf("  "); // Otherwise print an empty space
            }
        }
        MacUILib_printf("\n");
    }

    MacUILib_printf("\n==============================================\n");

    MacUILib_printf("Welcome to the snake game !!!\n");
    MacUILib_printf("Please use the WASD characters to move, '.' to end the game and click SPACE to pause.\n");
    MacUILib_printf("Collect '0' food items to gain 50 points but increase your snake length by 10.");
    MacUILib_printf("Collet 'c' food items to gain 10 points.");
    MacUILib_printf("Collect as many apples as you can as well as some SPECIAL ones for some power ups.\n");
    MacUILib_printf("Have fun and remember, don't run into yourself.\n");

    MacUILib_printf("==============================================\n");

    //MacUILib_printf("%s\n", dirList[myPlayer->getDir()]);
    MacUILib_printf("Score: %d\n", myGM->getScore());
    //MacUILib_printf("Size: %d\n", myPlayer->getPlayerPos()->getSize());
    //MacUILib_printf("Food: %d\n", myGM->getFood()->getFoodPos()->getSize());
    if (myGM->getLoseFlagStatus() == true){
        MacUILib_printf("You Lose :("); // Lose message
    } else if (myGM->getExitFlagStatus() == true) {
        MacUILib_printf("You ended the game."); // Quitting game early message
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
