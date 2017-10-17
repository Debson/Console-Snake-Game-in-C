/*
 * menu.h
 *
 *  Created on: October 10, 2017
 *      Author: DEBSON
 */

#ifndef MENU_MENU_H_
#define MENU_MENU_H_

#include <stdio.h>
#include <stdlib.h>


void gameWelcomeScreen();
int setKeyState();
float saveTime();
void writePlayerData();

enum {PLAY, HIGHSCORES, EXIT, ENTER};

extern LARGE_INTEGER frequency;
extern LARGE_INTEGER start;
extern LARGE_INTEGER end;
//extern FILE *file;


#endif /* MENU_MENU_H_ */
