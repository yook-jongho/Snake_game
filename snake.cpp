#include <ncurses.h>
#include <cstring>
#include "snake.h"
#include "map.h"
#include <iostream>

void Snake::Move(char dir)
{
    if (dir == 'l')
    {
        direction = 'l';
        body_x.push_front(head_x--);
        body_x.pop_back();
        body_y.push_front(head_y);
        body_y.pop_back();
    }
    if (dir == 'r')
    {
        direction = 'r';
        body_x.push_front(head_x++);
        body_x.pop_back();
        body_y.push_front(head_y);
        body_y.pop_back();
    }
    if (dir == 'u')
    {
        direction = 'u';
        body_y.push_front(head_y--);
        body_y.pop_back();
        body_x.push_front(head_x);
        body_x.pop_back();
    }
    if (dir == 'd')
    {
        direction = 'd';
        body_y.push_front(head_y++);
        body_y.pop_back();
        body_x.push_front(head_x);
        body_x.pop_back();
    }
}
void Snake::Draw(char v[][25], int x, int y, int len, char dir)
{
    v[y][x] = '@';
    int s = body_y.size();
    if (s == 0)
    {
        body_x.push_back(13);
        body_x.push_back(14);
        body_x.push_back(15);
        body_y.push_back(13);
        body_y.push_back(13);
        body_y.push_back(13);
    }
    for (int i = 1; i < s; i++)
    {
        v[body_y[i]][body_x[i]] = '0';
    }
    tail_x = x;
    tail_y = y;
}
/*
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
*/
//void Controll(char v[][25], int x, int y);
void Snake::makeBon(int x, int y, char dir)
{
    body_y.push_front(y);
    body_x.push_front(x);
    bondir.insert(bondir.begin(), dir);
}
void Snake::removeBon()
{
    body_y.pop_back();
    body_x.pop_back();
    bondir.pop_back();
};