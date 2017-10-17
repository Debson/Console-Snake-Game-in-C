/*
 * snake.h
 *
 *  Created on: October 10, 2017
 *      Author: DEBSON
 */

#ifndef SNAKE_SNAKE_H_
#define SNAKE_SNAKE_H_

#define CONSOLE_W 110
#define CONSOLE_H 44

#define KEY_RIGHT 77
#define KEY_LEFT 75
#define KEY_UP 72
#define KEY_DOWN 80

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

typedef struct
{
    int sxy[4096]; /* Maximum snake's length */
    int head;
    int direction;
    int length;
    int score;

} SNAKE;

extern int food[2];
extern int GAME;
extern SNAKE s;
extern double interval;

inline short getX(int xy);
inline short getY(int xy);

void initializeSnake();
SNAKE * snake();
void drawSnake(SNAKE *tsn);
void clearScreen();
void setBorders();

enum {slow = 200, medium = 100, fast = 50, impossible = 20};
enum {right, left, up, down};


#endif /* SNAKE_SNAKE_H_ */
