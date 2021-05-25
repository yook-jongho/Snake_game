#include <ncurses.h>
#include <cstring>
#include "snake.h"
#include "map.h"

void Snake::init_pos(char v[][25])
{
    direction = 'l';
    for (int i = 0; i < 3; i++)
    {
        if (i == 0)
        {
            v[13][13 + i] = '@';
        }
        else
        {
            v[13][13 + i] = '0';
        }
    }
}

void Snake::Move(char v[][25], int x, int y)
{
    for (int i = 0; i < 3; i++)
    {
        v[x][y + i] = ' ';
    }

    for (int i = 0; i < 3; i++)
    {
        if (i == 0)
        {
            v[x][(y - 1) + i] = '@';
        }
        else
        {
            v[x][(y - 1) + i] = '0';
        }
    }
}