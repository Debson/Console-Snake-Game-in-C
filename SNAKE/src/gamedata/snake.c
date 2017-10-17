/*
 * snake.c
 *
 *  Created on: October 10, 2017
 *      Author: DEBSON
 */

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "snake.h"
#include "../menu/menu.h"
#include "../interface/console.h"


/*
* TODO add options for speed, score, write score to .txt and read from .txt
* if want to see  all time highscores
*/
SNAKE s; /* Create new structure - snake */
int GAME = 1;

/* Flags required to control snake movement(can't go backward in any direction) */
int rightDirection  = 1;
int leftDirection   = 0;
int upDirection     = 0;
int downDirection   = 0;


double interval; /* Double variable for keeping game time */
char snakeShape = '*'; /* Shape of snake body, can put any character in ' ' quotes */
int food[2]; /* Tab for x and y coordinates of food */

/* Inline functions to get snake coordinates from buffor */
inline short getX(int xy)
{
    return (short)(xy>>16);
}

inline short getY(int xy)
{
    return (short)(xy);
}

/* Insertion of snake attributes */
void initializeSnake(void)
{
    snake()->head = 0;
    snake()->sxy[0] = (70<<16) + 20; /* Snake coordinates, x = 70, y = 20. Used logical shift in 32 bit buffor for x,y in purpose to save memory and it's very practical*/
    snake()->direction = right;
    snake()->length = 5;
    snake()->score;
    // ********************************************************************

    /* Printing first food in console in random location */
    food[0] = rand() % 70 + 20;
    food[1] = rand() % 30 + 4;
    GoToXY(food[0], food[1]);
    printf("O");

}

/* Function which returns address SNAKE structure.
By creating this function it is possible to insert to snake structure values and give address to that structure in other files*/
SNAKE * snake(int n)
{
    if(n == 1)
        initializeSnake();

    return &s;
}

int checkIfFoodEaten(SNAKE * tsn, int x, int y)
{
    int i;
    int x1 = 0, y1 = 0;

    if((food[0] == x) && (food[1] == y))
    {
        while(1)
        {
            x1 = rand() % 70 + 20;
            y1 = rand() % 30 + 4;

            if(x1 == food[0] && y1 == food[1])
                continue;

            if(!checkIfBodyBiten(tsn, x1, y1))
                break;
        }

        food[0] = x1;
        food[1] = y1;
        tsn->length++;
        tsn->score++;

    }
    /* Checking if snake head hits walls */
    if(x > 88 | x < 21)
        return 1;
    if(y < 4 | y > 32)
        return 1;

}

int checkIfBodyBiten(SNAKE * tsn, int x, int y)
{
    int i;
    int head = tsn->head - 1;

    if(tsn->length == 1)
        return 0;

    for(i = 0; i < tsn->length; i++)
    {
        if((x == getX(tsn->sxy[head])) && (y == getY(tsn->sxy[head])))
            return 1;
        head = (head - 1) & 4095; /* Bit mask for making 4096 sized array as buffor */
    }

    if(checkIfFoodEaten(tsn, x, y) == 1)
        return 1;

    return 0;
}

void drawSnake(SNAKE *tsn)
{
    int i;
    int head = tsn->head, tail = 0;

    int X = getX(tsn->sxy[head]);
    int Y = getY(tsn->sxy[head]);

    int check_result;

    switch(tsn->direction)
    {
        case right:
            {
                if(rightDirection)
                {
                    leftDirection = 0;
                    upDirection = 1;
                    downDirection = 1;
                    X++;
                } else X--;
            } break;
        case left:
            {
                if(leftDirection)
                {
                    rightDirection = 0;
                    upDirection = 1;
                    downDirection = 1;
                    X--;
                } else X++;
           } break;
        case up:
            {
                if(upDirection)
                {
                    leftDirection = 1;
                    rightDirection = 1;
                    downDirection = 0;
                    Y--;
                } else Y++;
            } break;
        case down:
            {
                if(downDirection)
                {
                    leftDirection = 1;
                    rightDirection = 1;
                    upDirection = 0;
                    Y++;
                } else Y--;
            } break;
    }

    check_result = checkIfBodyBiten(tsn, X, Y); // Flag for eating itself error

    if(check_result == 1)
    {
        GAME = 0; /* Ends game lopp */
        saveTime(); /* Function saving time when game ended */
        writePlayerData(tsn); /* Function writing information about player in .txt file */
        GoToXY(1, 50);
    }
    head = (head + 1) & 4095; /* Bit mask for making 4096 sized array as buffor */

    tsn->head = head;
    tsn->sxy[head] = (X<<16) | Y;

    GoToXY(X, Y);
    printf("%c", snakeShape);

    tail = (head - tsn->length) & 4095;
    GoToXY(getX(tsn->sxy[tail]), getY(tsn->sxy[tail]));
    printf(" ");

    GoToXY(food[0], food[1]);
    printf("O");

    /* Settings borders of map */
    setTextColor(10);
    setBorders();
    setTextColor(15);

    /* Printing current score and gametime */
    setTextColor(12);
    GoToXY(20, 37);
    printf("SCORE: %d", tsn->score);

    GoToXY(20, 38);
    QueryPerformanceCounter(&end);
    interval = (double) (end.QuadPart - start.QuadPart) / frequency.QuadPart;

    printf("Game lasts %3.3f seconds", interval);
    setTextColor(15);



}

/* Setting in which way snake have to go after clicking control buttons */
void setDirection(SNAKE *tsn)
{

    if(GetKeyState(VK_RIGHT) < 0)
        tsn->direction = right;


    if(GetKeyState(VK_LEFT) < 0)
        tsn->direction = left;


    if(GetKeyState(VK_UP) < 0)
        tsn->direction = up;


    if(GetKeyState(VK_DOWN) < 0)
        tsn->direction = down;

}

void setBorders()
{
    int i;
    char c = '!';
    int borderX = 20;
    int borderY = 3;

    adjustWindowSize(CONSOLE_W, CONSOLE_H);
    GoToXY(borderX, borderY);

    for(i = 0; i < 70; i++)
    {
        printf("%c", c);
    }

    for(i = 0; i < 30; i++)
    {
        GoToXY(borderX, i+borderY);
        printf("%c\n", c);
    }

    GoToXY(borderX, borderY + 30);
    for(i = 0; i< 70; i++)
    {
        printf("%c", c);
    }

    GoToXY(borderX + 70, borderY);
    for(i = 0; i< 30; i++)
    {
        GoToXY(borderX + 69, i+borderY);
        printf("%c\n", c);
    }

}
