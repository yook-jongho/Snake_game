#include <ncurses.h>
#include <cstring>
#include "snake.h"
#include "map.h"
#include <iostream>

void Snake::Move(char dir)
{
    if (dir == 'l')
    {
        head_x--;
    }
    if (dir == 'r')
    {
        head_x++;
    }
    if (dir == 'u')
    {
        head_y--;
    }
    if (dir == 'd')
    {
        head_y++;
    }
}
void Snake::Draw(char v[][25], int x, int y, int len, char dir)
{

    v[y][x] = '@';
    int curv = 0;
    int count = 0;
    int s = bondir.size();
    for (int a = 0; a < s; a += 2)
    {
        if (x == bon[a])
        {
            if (y < bon[a + 1])
            {
                while (y != bon[a + 1])
                {
                    y++;
                    v[y][x] = '0';
                    count++;
                }
            }
            else
            {
                while (y != bon[a + 1])
                {
                    y--;
                    v[y][x] = '0';
                    count++;
                }
            }
        }
        if (y == bon[a])
        {
            if (x < bon[a + 1])
            {
                while (y != bon[a + 1])
                {
                    x++;
                    v[y][x] = '0';
                    count++;
                }
            }
            else
            {
                while (x != bon[a + 1])
                {
                    x--;
                    v[y][x] = '0';
                    count++;
                }
            }
        }
    }
    if (s == 0 || count != len)
    {
        if (dir == 'l')
        {
            while (count != len)
            {
                x++;
                v[y][x] = '0';
                count++;
            }
        }
        if (dir == 'r')
        {
            while (count != len)
            {
                x--;
                v[y][x] = '0';
                count++;
            }
        }
        if (dir == 'u')
        {
            while (count != len)
            {
                y--;
                v[y][x] = '0';
                count++;
            }
        }
        if (dir == 'd')
        {
            while (count != len)
            {
                y++;
                v[y][x] = '0';
                count++;
            }
        }
    }
    tail_x = x;
    tail_y = y;
}
//void Controll(char v[][25], int x, int y);
void Snake::makeBon(int x, int y, char dir)
{
    bon.insert(bon.begin(), y);
    bon.insert(bon.begin(), x);
    bondir.insert(bondir.begin(), dir);
}
void Snake::removeBon()
{
    bon.pop_back();
    bon.pop_back();
    bondir.pop_back();
};