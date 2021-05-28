#include <ncurses.h>
#include "manager.h"

int Manager::gameScore(char item)
{
    if (item == '$')
    {
        score += 10;
    }
    return score;
}