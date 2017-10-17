/*
 * menu.c
 *
 *  Created on: October 10, 2017
 *      Author: DEBSON
 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "../interface/console.h"
#include "../gamedata/snake.h"
#include "menu.h"


LARGE_INTEGER frequency;
LARGE_INTEGER start;
LARGE_INTEGER end;

FILE *file;

void setName();
void gameStarting();

int MENU_BREAK          = 0;
int flagPLAY            = 1;
int flagRECENT_GAMES    = 1;
int flagEXIT            = 1;

int key1_lock = 1;
int key2_lock = 1;
int key3_lock = 1;
int key4_lock = 1;
char *name;
static int cnt = 0;


void gameWelcomeScreen()
{

    adjustWindowSize(CONSOLE_W, CONSOLE_H);
    clearScreen();
    drawGameName();

    while(1)
    {

    if(MENU_BREAK) break;

    switch(setKeyState())
    {
        case 0:
            {
                if(flagPLAY)
                {
                    flagPLAY = 0;
                    flagRECENT_GAMES= 1;
                    flagEXIT = 1;

                    setTextColor(10);
                    GoToXY(8, 30);
                    puts("PLAY");

                    setTextColor(15);
                    GoToXY(8, 31);
                    puts("RECENT GAMES");

                    setTextColor(15);
                    GoToXY(8, 32);
                    puts("EXIT");
                }

            } break;
        case 1:
            {
                if(flagRECENT_GAMES)
                {
                    flagPLAY = 1;
                    flagRECENT_GAMES = 0;
                    flagEXIT = 1;

                    setTextColor(15);
                    GoToXY(8, 30);
                    puts("PLAY");

                    setTextColor(10);
                    GoToXY(8, 31);
                    puts("RECENT GAMES");

                    setTextColor(15);
                    GoToXY(8, 32);
                    puts("EXIT");
                }

            } break;
        case 2:
            {
                if(flagEXIT)
                {
                    flagPLAY = 1;
                    flagRECENT_GAMES = 1;
                    flagEXIT = 0;

                    setTextColor(15);
                    GoToXY(8, 30);
                    puts("PLAY");

                    setTextColor(15);
                    GoToXY(8, 31);
                    puts("RECENT GAMES");

                    setTextColor(10);
                    GoToXY(8, 32);
                    puts("EXIT");
                }

            } break;
        case 4:
            {
                setTextColor(15);

                if(!flagEXIT)
                {
                    MENU_BREAK = 1;
                    GAME = 0;
                }

                if(!flagPLAY)
                {
                    MENU_BREAK = 1;
                    clearScreen();


                        setName();

                    gameStarting();
                }

                if(!flagRECENT_GAMES)
                {
                     clearScreen();
                     file = fopen("src/player_data.txt", "r");

                    char read = 0;
                     while(read != EOF)
                     {
                         putchar(read = getc(file));

                     }

                    getchar();
                    while(1)
                    {

                        if(getchar() == 10)
                            break;
                    }
                    fclose(file);

                    flagPLAY = 1;
                    flagRECENT_GAMES= 1;
                    flagEXIT = 1;

                    clearScreen();
                    drawGameName();
                    setTextColor(15);
                    GoToXY(8, 30);
                    puts("PLAY");

                    setTextColor(10);
                    GoToXY(8, 31);
                    puts("RECENT GAMES");

                    setTextColor(15);
                    GoToXY(8, 32);
                    puts("EXIT");

                }

            } break;
        }
    }
    //setDelay(2000);
    clearScreen();

}

void drawGameName()
{
    GoToXY(0, 10);
    setTextColor(12);
    puts("\n\
                                 _______..__   __.      ___       __  ___  _______  \n\
                                /       ||  \\ |  |     /   \\     |  |/  / |   ____| \n\
                               |   (----`|   \\|  |    /  ^  \\    |  '  /  |  |__    \n\
                                \\   \\    |  . `  |   /  /_\\  \\   |    <   |   __|   \n\
                            .----)   |   |  |\\   |  /  _____  \\  |  .  \\  |  |____  \n\
                            |_______/    |__| \\__| /__/     \\__\\ |__|\\__\\ |_______|  "
         );

    setTextColor(15);
    GoToXY(72, 17);
    puts("by   debson");

}

void gameStarting()
{
                    GoToXY(CONSOLE_W/2, CONSOLE_H/2);
                    puts("3");
                    setDelay(500);
                    clearScreen();

                    GoToXY(CONSOLE_W/2, CONSOLE_H/2);
                    puts("2");
                    setDelay(400);
                    clearScreen();

                    GoToXY(CONSOLE_W/2, CONSOLE_H/2);
                    puts("1");
                    setDelay(300);
                    clearScreen();

                    GoToXY(CONSOLE_W/2, CONSOLE_H/2);
                    puts("GO!");
                    setDelay(200);
                    clearScreen();
                    QueryPerformanceFrequency(&frequency);
                    QueryPerformanceCounter(&start);

}

void setName()
{
    name = malloc( 25 * sizeof *name);

    setTextColor(12);
    GoToXY(35, 22);
    puts("ENTER NAME: ");
    setTextColor(15);
    scanf("%c", name);
    GoToXY(46, 22);
    scanf("%s", name);
    clearScreen();

}

float saveTime()
{
    float gameTime;
    gameTime = interval;

    return interval;
}

void writePlayerData(SNAKE * tsn)
{
    int i;

    file = fopen("src/player_data.txt", "a+");
    time_t playerDate = time(NULL);

    /*
    * Obtaining data about precise date+time when player started game
    * Saving to file src/player_data.txt player's game info in this format: name, score, date of a game
    */
    fprintf(file, "Name: %s\n", name);
    fprintf(file, "Score: %d\n", tsn->score);
    fprintf(file, "Gametime: %3.3f sec\n", saveTime());
    fprintf(file, "Date: %s", ctime(&playerDate));
    for(i = 0; i < 40; i++)
        fprintf(file, "=");
    fprintf(file, "\n");

    fclose(file);


}


int setKeyState()
{

    if(cnt == 4) // If enter is clicked it changes value of cnt to 1, used to come back at the same position in menu after clicking enter in "RECENT GAMES"
        cnt = 1;

    if(GetKeyState(VK_UP) < 0 && key1_lock)
    {
        key1_lock = 0;
        key2_lock = 1;
        cnt--;

        if(cnt < 0)
            cnt = 0;

    }
    else if(GetKeyState(VK_UP) == 1 | GetKeyState(VK_UP) == 0)
        key1_lock = 1;

    //if(key == upMenu) key1_lock = 1;

    if(GetKeyState(VK_DOWN) < 0 && key2_lock)
    {
        key2_lock = 0;
        key1_lock = 1;
        cnt++;

        if(cnt > 2)
            cnt = 2;

    }
    else if(GetKeyState(VK_DOWN) == 1 | GetKeyState(VK_DOWN) == 0)
        key2_lock = 1;

    if(GetKeyState(VK_RETURN) < 0)
            cnt = 4;

    return cnt;
}


