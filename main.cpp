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
        m.render();     //화면 렌더링
        usleep(500000); // 0.5 딜레이
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