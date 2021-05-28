#include <ncurses.h>
#include "manager.h"

int Manager::gameScore(bool check, int score)
{
    if (check)
    {
        score += 10;
    }
    return score;
}