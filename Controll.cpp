#include <ncurses.h>
#include "map.h"
#include "snake.h"
#include "Controll.h"

char Controll::controll(char dir)
{
    int key;
    nodelay(stdscr, true);
    key = getch();
    keypad(stdscr, TRUE);
    curs_set(0);
    noecho();

    switch (key)
    {
    case KEY_UP:
        dir = 'u';
        break;
    case KEY_LEFT:
        dir = 'l';
        break;
    case KEY_RIGHT:
        dir = 'r';
        break;
    case KEY_DOWN:
        dir = 'd';
        break;
    default:
        break;
    }

    return dir;
}