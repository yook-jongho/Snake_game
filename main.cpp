#include <ncurses.h>
#include <unistd.h>
#include "snake.h"
#include "map.h"
#include <iostream>

using namespace std;
int main()
{
    Map m;
    // Snake s;
    int i = 0;
    for (int i = 0; i < 4; i++)
    {
        m.getMap(i);
        if (m.islevelup)
        {
            i = 0;
            break;
        }
        while (1)
        {
            m.render();     //화면 렌더링
            usleep(100000); // 0.1 딜레이
            if (!m.gameOver)
            {
                //게임 재시작 함수 호출,  false이면, break. true이면 continue.
                usleep(10000000);
                break;
            }
        }
    }
    endwin();

    return 0;
}