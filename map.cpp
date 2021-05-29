#include <fstream>
#include <random>
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
int i = 0;
bool check1 = true;
bool check2 = true;

int item_gx, item_gy = 0;
int item_sx, item_sy = 0;
int score = 0;

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

    if (!check1 || !check2)
    {
        for (int i = 0; i < 25; i++)
        {
            for (int j = 0; j < 25; j++)
            {
                if (!check1)
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
                    s.head_x = j;
                    s.head_y = i;
                    v[i][j] = '0';
                }
            }
        }
        bool check_gitem = c.check_item(s.head_x, s.head_y, item_gx, item_gy);
        bool check_sitem = c.check_item(s.head_x, s.head_y, item_sx, item_sy);
        score = manager.gameScore(check_gitem, check_sitem, score);
        s.length = manager.snakeLength(check_gitem, check_sitem, s.length);
        s.Move(a);
        s.Draw(v, s.head_x, s.head_y, s.length, a);
        s.direction = b;
        grow_item();
        small_item();
        i++;
    }
}

void Map::grow_item()
{
    if (i == 50)
    {
        if (item_gx >= 0 || item_gy >= 0)
        {
            v[item_gx][item_gy] = ' ';
        }
        random_device rd;
        mt19937 gen(rd());

        uniform_int_distribution<int> dis(1, 23);

        item_gx = dis(gen);
        item_gy = dis(gen);

        v[item_gx][item_gy] = 'G';
    }
}

void Map::small_item()
{
    if (i == 50)
    {
        if (item_sx >= 0 || item_sy >= 0)
        {
            v[item_sx][item_sy] = ' ';
        }
        random_device rd;
        mt19937 gen(rd());

        uniform_int_distribution<int> dis(1, 23);

        item_sx = dis(gen);
        item_sy = dis(gen);

        v[item_sx][item_sy] = 'S';
        i = 0;
    }
}