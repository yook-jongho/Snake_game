#include <ncurses.h>
#include <unistd.h>
#include "snake.h"
#include "map.h"

Map m;
int main()
{
    // Snake s;
    // int a = 1;
    m.getMap();
    while (1)
    {
        m.render();
        usleep(500000);
    }
    endwin();
    // while (a < 10)
    // {
    //     a++;
    //     usleep(500000);
    // }
    // endwin();
    return 0;
}