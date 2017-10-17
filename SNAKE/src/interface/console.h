/*
 * console.h
 *
 *  Created on: October 10, 2017
 *      Author: DEBSON
 */

#ifndef CONSOLE_CONSOLE_H_
#define CONSOLE_CONSOLE_H_

#include <stdio.h>

/* Function for console and game control */
void GoToXY(int column, int line);
void setDelay(int delay);
void clearScreen();
void setTextColor(int ForgC);
void clearConsoleToColors(int ForgC, int BackC);
void adjustWindowSize(int WIDTH, int HEIGHT);

#endif /* CONSOLE_CONSOLE_H_ */
