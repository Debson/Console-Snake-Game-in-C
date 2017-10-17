/*
 * main.c
 *
 *  Created on: October 10, 2017
 *      Author: DEBSON
 */

#include <stdlib.h>
#include <stdio.h>

#include "gamedata/snake.h" /* Snake header to get access to main snake functions*/
#include "interface/console.h"

int speed;
speed = fast; /* Choose speed from: @slow, @medium, @fast, @impossible */

int main(void)
{
    initializeSnake(); /* @SNAKE Initialization */

    gameWelcomeScreen(); /* Setting up borders of our field of game */

    /* Main game loop */
        while(GAME)
        {
            /* Function to draw snake body, function to get snake directory after clicking any movement control button,
                and delay function responsible for snake moving speed.*/
            drawSnake(&s);
            setDirection(&s);
            setDelay(speed);
        }


    GoToXY(10, 38);
    system("pause"); /* Function to not close console window after exit from game */
    return 0;
}
