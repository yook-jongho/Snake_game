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
        usleep(200000); // 0.1 딜레이
        if (!m.render())
        {
            //게임 재시작 함수 호출,  false이면, break. true이면 continue.
            usleep(10000000);
            break;
        }
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