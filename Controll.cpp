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

bool Controll::check_dir(char dir1, char dir2)
{
    bool check;
    if ((dir1 == 'u' && dir2 == 'd') || (dir1 == 'd' && dir2 == 'u') || (dir1 == 'l' && dir2 == 'r') || (dir1 == 'r' && dir2 == 'l'))
    {
        check = false;
    }
    else
    {
        check = true;
    }
    return check;
}