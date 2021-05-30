#include "snake.h"

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
void Snake::Draw(char v[][25], int x, int y, int len)
{
    v[y][x] = '@';
    int s = len;
    if (s == 0)
    {
        body_x.push_back(13);
        body_x.push_back(14);
        body_y.push_back(13);
        body_y.push_back(13);
    }
    for (int i = 0; i < s - 1; i++)
    {
        v[body_y[i]][body_x[i]] = '0';
    }
    tail_x = x;
    tail_y = y;
}
