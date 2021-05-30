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

char sucess1 = 'x';
char sucess2 = 'x';
char sucess3 = 'x';
char sucess4 = 'x';

//게임 화면을 그리는 함수
void Map::render()
{

    initscr();
    resize_term(60, 100);

    border('+', '+', '+', '+', '*', '*', '*', '*');
    refresh(); //환기하는거

    mvprintw(2, 9, "<<snake game>>");

    WINDOW *gamebox; //게임 화면을 나타내주는 박스 = 뱀이 기어다니는 곳
    gamebox = newwin(25, 25, 3, 3);

    WINDOW *scoreBox;
    scoreBox = newwin(6, 16, 3, 40);
    box(scoreBox, 0, 0); //테두리를 표시. box 영역
    mvwprintw(scoreBox, 1, 1, "score : %d", score);
    mvwprintw(scoreBox, 2, 1, " %d /  %d ", s.length + 1, 13);
    mvwprintw(scoreBox, 3, 1, "+ : %d", count_gitem);
    mvwprintw(scoreBox, 4, 1, "- : %d", count_sitem);

    WINDOW *MissonBox;
    MissonBox = newwin(7, 16, 10, 40);
    box(MissonBox, 0, 0); //테두리를 표시. box 영역
    mvwprintw(MissonBox, 1, 1, "Misson");
    mvwprintw(MissonBox, 2, 1, "B: 20 %c", sucess1);
    mvwprintw(MissonBox, 3, 1, "B: 20 %c", sucess2);
    mvwprintw(MissonBox, 4, 1, "+ : 2 %c", sucess3);
    mvwprintw(MissonBox, 5, 1, "- : 0 %c", sucess4);

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
        if (!check1)
        {
            mvprintw(3, 3, "because of input opposite key");
        }
        if (!check2)
        {
            mvprintw(3, 3, "because of complict the wall");
        }
    }

    wrefresh(gamebox);
    refresh();
    wrefresh(scoreBox);
    wrefresh(MissonBox);

    //inner box
    //s.Move(14);
    delwin(gamebox);
    delwin(scoreBox);
    delwin(MissonBox);

    if (!check1 || !check2)
    {
        gameOver = false;
    }
    else
    {
        gameOver = true;
    }
}

//map 파일을 받아와 배열에 저장.
void Map::getMap(int l)
{
    int i = 0;

    ifstream infile;
    if (level == 0)
    {

        infile.open("map1.txt");
    }
    else if (level == 1)
    {
        infile.open("map2.txt");
    }
    else if (level == 2)
    {
        infile.open("map3.txt");
    }
    else
    {
        infile.open("map4.txt");
    }
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
                v[i][j] = ' ';
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

        s.Move(a);
        s.Draw(v, s.head_x, s.head_y, s.length);
        s.direction = b;

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
        levelUp(score, s.length, count_gitem, count_sitem);
        if (score > 20)
        {
            sucess1 = '0';
        }
        else if (s.length > 4)
        {
            sucess2 = '0';
        }
        else if (count_gitem > 2)
        {
            sucess3 = '0';
        }
        else
        {
            sucess4 = '0';
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

void Map::levelUp(int score, int length, int plus, int minus)
{
    if (score % 10 >= 2 && length >= 4 && plus >= 1 && minus >= 0)
    {
        islevelup = true;
    }
    else
    {
        islevelup = false;
    }
}
