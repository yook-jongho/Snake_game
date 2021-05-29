#include <ncurses.h>
#include "manager.h"

int Manager::gameScore(bool check, bool check2, int score)
{
    if (check)
    {
        score += 10;
    }
    if (check2)
    {
        score -= 10;
    }
    return score;
}

int Manager::snakeLength(bool check, bool check2, int len)
{
    if (check)
    {
        len += 1;
    }
    if (check2)
    {
        len -= 1;
    }
    return len;
}