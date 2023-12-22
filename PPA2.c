#include <stdio.h>
#include "MacUILib.h"

// PPA2 GOAL: 
//       Construct the game backbone where the player can control an object 
//       to move freely in the game board area with border wraparound behaviour.

// Watch Briefing Video and Read Lab Manual before starting on the activity!



// PREPROCESSOR CONSTANTS DEFINITION HERE
/////////////////////////////////////////
int i, j; 
int dimX;
int dimY;
double delay;

// GLOBAL VARIABLE DEFINITION HERE
/////////////////////////////////////////

int exitFlag; // Program Exiting Flag - old stuff

// For storing the user input - from PPA1
char input;

// [TODO] : Define objPos structure here as described in the lab document
struct objPos
{
    int x; 
    int y;
    char symbol;
};

struct objPos objPost;

char gameBoard[10][20];

// [TODO] : Define the Direction enumeration here as described in the lab document
//          This will be the key ingredient to construct a simple Finite State Machine
//          For our console game backbone.

enum direction {STOP, LEFT, RIGHT, UP, DOWN};
enum direction dirMode;

// enum level {Lev1 = 1, Lev2 =3, Lev3, Lev4, Lev5};
// enum level Levels;


// FUNCTION PROTOTYPING DEFINITION HERE
/////////////////////////////////////////

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);

// You may insert additional helper function prototypes below.
// 
// As a good practice, always insert prototype before main() and implementation after main()
// For ease of code management.



// MAIN PROGRAM LOOP
/////////////////////////////////////////
// This part should be intuitive by now.
// DO NOT TOUCH

int main(void)
{

    Initialize();

    while(!exitFlag)  
    {
        GetInput();

        RunLogic();

        DrawScreen();

        LoopDelay();
    }

    CleanUp();

}


// INITIALIZATION ROUTINE
/////////////////////////////////////////
void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();

    input = 0; // NULL
    exitFlag = 0;  // not exiting    
   
    // [TODO] : Initialize more variables here as seen needed.
    //          PARTICULARLY for the structs!!
 

    objPost.x  = 10;
    objPost.y = 5;
    objPost.symbol = 'P';

    dimX = 20;
    dimY = 10;
    

    // 5 levels
    // Levels = Lev1;
    delay = 10000;
    dirMode = STOP;
    
}


// INPUT PROCESSING ROUTINE
/////////////////////////////////////////
void GetInput(void)
{
    // [TODO] : Implement Asynchronous Input - non blocking character read-in    
    //          (Same as PPA1)
    if (MacUILib_hasChar())
    {
        input = MacUILib_getChar();
    }

}


// PROGRAM LOGIC ROUTINE
/////////////////////////////////////////
void RunLogic(void)
{
    // [TODO] : First, process the input by mapping
    //          WASD to the corresponding change in player object movement direction

    if(input != 0)  // if not null character
    {
        switch(input)
        {                      
            case ' ':  // exit
                exitFlag = 1;
                break;

            // Add more key processing here
            // w up, s down, a left, d right
            case 'w':
            case 'W':
                dirMode = UP;
                break;


            case 's':
            case 'S':
                dirMode = DOWN;
                break;

            case 'a':
            case 'A':
                dirMode = LEFT;
                break;

            case 'd':
            case 'D':
                dirMode = RIGHT;
                break;

            case '5':
                // Levels = Lev5;
                delay = 300000;
                break;
   
            case '6':
                // Levels = Lev4;
                delay = 120000;
                break;

            case '7':
                // Levels = Lev3;
                delay = 80000;
                break;

            case '8':
                // Levels = Lev2;
                delay = 30000;
                break;        

            case '9':
                // Levels = Lev1;
                delay = 10000;
                break;

            default: //default if nothing happens
                break;
        }
        input = 0;
    }



    // [TODO] : Next, you need to update the player location by 1 unit 
    //          in the direction stored in the program

    // [TODO] : Heed the border wraparound!!!

    switch (dirMode)
    {
        case UP:
            if (input == 'A' || input == 'a')
            {
                dirMode = LEFT;
            }
            else if (input == 'D' || input == 'd')
            {
                dirMode = RIGHT;
            }
            
            // if(objPost.y >= dimY-2)
            // {
            //     objPost.y = 1;
            // }
            if(objPost.y <= 1)
            {
                objPost.y = dimY-1;
            }
            objPost.y--; 
            
        break;

        case DOWN:
            if (input == 'A' || input == 'a')
            {
                dirMode = LEFT;
            }
            else if (input == 'D' || input == 'd')
            {
                dirMode = RIGHT;
            }

            
            if(objPost.y >= dimY-2)
            {
                objPost.y = 0;
            }
            // else if(objPost.y <= 1)
            // {
            //     objPost.y = dimY-1;
            // }
            objPost.y++;
        break;

        case LEFT:
            if (input == 'w' || input == 'W')
            {
                dirMode = UP;
            }
            else if (input == 'S' || input == 's')
            {
                dirMode = DOWN;
            }
            

            // if(objPost.x >= dimX-1)
            // {
            //     objPost.x = 1;
            // }
            if(objPost.x <= 1)
            {
                objPost.x = dimX-1;
            }
            objPost.x--;
            break;

        case RIGHT:
            if (input == 'w' || input == 'W')
            {
                dirMode = UP;
            }
            else if (input == 'S' || input == 's')
            {
                dirMode = DOWN;
            }

            
            if(objPost.x >= dimX-2)
            {
                objPost.x = 0;
            }
            // else if(objPost.x == 0)
            // {
            //     objPost.x = dimX-1;
            // }
            objPost.x++;
            break;

        default:
            break;
    }

}



// SCREEN DRAWING ROUTINE
/////////////////////////////////////////
void DrawScreen(void)
{
    // [TODO] : Implement the latest drawing logic as described in the lab manual
    //
    //  1. clear the current screen contents

    //  2. Iterate through each character location on the game board
    //     using the nested for-loop row-scanning setup.

    //  3. For every visited character location on the game board
    //          If on border on the game board, print a special character
    //          If at the player object position, print the player symbol
    //          Otherwise, print the space character
    //     Think about how you can format the screen contents to achieve the
    //     same layout as presented in the lab manual

    //  4. Print any debugging messages as seen needed below the game board.
    //     As discussed in class, leave these debugging messages in the program
    //     throughout your dev process, and only remove them when you are ready to release
    //     your code. 
    
    MacUILib_clearScreen();

    MacUILib_printf("Player Speed(change through 5-9): %.2f\ns", delay/100000);
    switch (dirMode)
    {
        case STOP:
            MacUILib_printf("Player Direction: STOP\n");
        break;

        case UP:
            MacUILib_printf("Player Direction: UP\n");
        break;

        case DOWN:
            MacUILib_printf("Player Direction: DOWN\n");
        break;

        case LEFT:
            MacUILib_printf("Player Direction: LEFT\n");
            break;

        case RIGHT:
            MacUILib_printf("Player Direction: RIGHT\n");
            break;

        default:
            break;
    }
    MacUILib_printf("Player Position [%d, %d] \n", objPost.x, objPost.y);
    MacUILib_printf("Player Symbol: %c\n", objPost.symbol);
    MacUILib_printf("Press spacebar to exit the game!\n");
   

    //dimy is rows; dimx is columns
    for(i = 0; i<dimY; i++) //rows
    {
        for(j = 0; j<dimX; j++) //columns
        {
            if (i == objPost.y && j == objPost.x)
            {
                gameBoard[i][j] = objPost.symbol;
            }
            else if (i == 0 || i == dimY-1)
            {
                gameBoard[i][j] = '#';
            }
            else if (j == 0 || j == dimX - 1)
            {
                gameBoard[i][j] = '#';
            }
            else
            {
                gameBoard[i][j] = ' ';
            }
            MacUILib_printf("%c",gameBoard[i][j]);
        }
        MacUILib_printf("\n");
    }
}



// PROGRAM LOOOP DELAYER ROUTINE
/////////////////////////////////////////
void LoopDelay(void)
{
    // Change the delaying constant to vary the movement speed.
    // MacUILib_printf("%c", Levels);
    MacUILib_Delay(delay);    
}



// PROGRAM CLEANUP ROUTINE
/////////////////////////////////////////
// Recall from PPA1 - this is run only once at the end of the program
// for garbage collection and exit messages.
void CleanUp(void)
{
    MacUILib_uninit();
}



