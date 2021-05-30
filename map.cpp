#include <fstream>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include <ncurses.h>

#include "map.h"
#include "snake.h"
#include "Controll.h"
#include "manager.h"

using namespace std;
Snake s;
Controll c;
Manager manager;
int grow_time, small_time = 0;
bool check1 = true;
bool check2 = true;

int item_gx, item_gy = 0;
int item_sx, item_sy = 0;
int potal_x, potal_y = 0;
int potal_x2, potal_y2 = 0;
int score = 0;

int gate[][2] = {{0}};
int count_gitem = 0;
int count_sitem = 0;
int potal_time = 0;
//게임 화면을 그리는 함수
bool Map::render()
{

    initscr();
    resize_term(60, 100);

    border('+', '+', '+', '+', '*', '*', '*', '*');
    refresh(); //환기하는거

    mvprintw(2, 9, "<<snake game>>");

    WINDOW *gamebox; //게임 화면을 나타내주는 박스 = 뱀이 기어다니는 곳
    gamebox = newwin(25, 25, 3, 3);

    WINDOW *scoreBox;
    scoreBox = newwin(12, 16, 3, 40);
    box(scoreBox, 0, 0); //테두리를 표시. box 영역
    mvwprintw(scoreBox, 1, 1, "score : %d", score);
    mvwprintw(scoreBox, 2, 1, " %d /  %d ", s.length, 13);
    mvwprintw(scoreBox, 3, 1, "+ : %d", count_gitem);
    mvwprintw(scoreBox, 4, 1, "- : %d", count_sitem);

    upDate();
    for (int i = 0; i < 25; i++)
    {
        for (int j = 0; j < 25; j++)
        {
            wprintw(gamebox, "%c", v[i][j]);
        }
    }
    if (!check1 || !check2)
    {
        mvprintw(2, 9, "<<game over>>");
    }

    refresh();
    wrefresh(gamebox);
    wrefresh(scoreBox);

    //inner box
    //s.Move(14);
    delwin(gamebox);
    delwin(scoreBox);

    if (!check1 || !check2)
    {
        return false;
    }
    else
    {
        return true;
    }
}

//map 파일을 받아와 배열에 저장.
void Map::getMap()
{
    int i = 0;

    ifstream infile;
    infile.open("map1.txt");
    char buffer[30];

    while (infile.getline(buffer, 30))
    {
        for (int j = 0; j < strlen(buffer); j++)
        {
            if (buffer[j] == '2')
            {
                v[i][j] = '*';
            }
            else if (buffer[j] == '1')
            {
                v[i][j] = '+';
            }
            else
            {
                v[i][j] = ' ';
            }
        }
        i++;
    }
    infile.close();
}

void Map::upDate()
{
    //뱀 머리의 방향 확인.
    char a = s.direction;
    char b = c.controll(a);
    check1 = c.check_dir(a, b);
    check2 = c.check_wall(s.head_x, s.head_y);

    if (!check1 || !check2 || s.length < 2)
    {
        for (int i = 0; i < 25; i++)
        {
            for (int j = 0; j < 25; j++)
            {
                if (!check1 || s.length < 2)
                {
                    v[i][j] = ' ';
                }
                else if (!check2)
                {
                    if (v[i][j] == '0')
                    {
                        v[i][j] = ' ';
                    }
                    else if (v[i][j] == '@')
                    {
                        v[i][j] = '+';
                    }
                }
            }
        }
    }
    else
    {
        for (int i = 0; i < 25; i++)
        {
            for (int j = 0; j < 25; j++)
            {
                if (v[i][j] == '0')
                    v[i][j] = ' ';
                if (v[i][j] == '@')
                {
                    v[i][j] = ' ';
                }
            }
        }
        bool check_gitem = c.check_item(s.head_x, s.head_y, item_gx, item_gy); //grow item을 먹었는지 check
        bool check_sitem = c.check_item(s.head_x, s.head_y, item_sx, item_sy); //small item을 먹었는지 check

        score = manager.gameScore(check_gitem, check_sitem, score);         //점수 계산
        s.length = manager.snakeLength(check_gitem, check_sitem, s.length); //길이 계산

        s.Draw(v, s.head_x, s.head_y, a, s.length);

        s.direction = b;
        s.Move(b, v, gate);

        grow_item();
        small_item();
        potal();

        grow_time++;
        small_time++;
        potal_time++;

        if (check_gitem)
        {
            count_gitem++;
        }
        if (check_sitem)
        {
            count_sitem++;
        }
    }
}

void Map::grow_item()
{
    if (grow_time == 50)
    {
        if (item_gx >= 0 || item_gy >= 0)
        {
            v[item_gx][item_gy] = ' ';
        }
        time_t t1 = time(NULL);
        srand(t1);
        item_gx = rand() % 23 + 1;
        time_t t2 = time(NULL);
        srand(t2);
        item_gy = rand() % 23 + 1;

        v[item_gx][item_gy] = 'G';
        grow_time = 0;
    }
}

void Map::small_item()
{
    if (small_time == 60)
    {
        if (item_sx >= 0 || item_sy >= 0)
        {
            v[item_sx][item_sy] = ' ';
        }
        time_t t3 = time(NULL);
        srand(t3);
        item_sx = rand() % 23 + 1;
        time_t t4 = time(NULL);
        srand(t4);
        item_sy = rand() % 23 + 1;

        v[item_sx][item_sy] = 'S';
        small_time = 0;
    }
}

void Map::potal()
{
    time_t tx;
    if (potal_time == 120)
    {
        if (potal_x >= 0 || potal_y >= 0)
        {
            v[potal_x][potal_y] = '+';
            v[potal_x2][potal_y2] = '+';
        }

        time_t tp = time(NULL);
        srand(tp);
        int random_num = rand() % 24;

        if (random_num % 2 == 0)
        {
            tx = time(NULL);
            srand(tx);
            potal_x = rand() % 23 + 1;
            potal_y = 0;

            potal_y2 = rand() % 23 + 1;
            potal_x2 = 0;
        }
        else
        {
            tx = time(NULL);
            srand(tx);
            potal_x = rand() % 23 + 1;
            potal_y = 24;

            potal_y2 = rand() % 23 + 1;
            potal_x2 = 24;
        }

        gate[0][0] = potal_x;
        gate[0][1] = potal_y;

        v[potal_x][potal_y] = '#';
        v[potal_x2][potal_y2] = '#';
        potal_time = 0;
    }
}
