#include <fstream>
#include <random>
#include <iostream>
#include <ncurses.h>
#include <vector>
#include <string>
#include <cstring>
#include "map.h"
#include "snake.h"
#include "Controll.h"

using namespace std;
Snake s;
Controll c;
int i = 0;

void Map::render()
{

    initscr();
    resize_term(60, 100);

    border('+', '+', '+', '+', '*', '*', '*', '*');
    refresh();

    mvprintw(2, 2, "<snake game>");

    WINDOW *gamebox;
    gamebox = newwin(25, 25, 3, 3);

    WINDOW *scoreBox;
    scoreBox = newwin(12, 10, 3, 30);
    box(scoreBox, 0, 0);

    upDate();
    for (int i = 0; i < 25; i++)
    {
        for (int j = 0; j < 25; j++)
        {
            wprintw(gamebox, "%c", v[i][j]);
        }
    }
    wrefresh(gamebox);
    wrefresh(scoreBox);

    //inner box
    //s.Move(14);
    delwin(gamebox);
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
    char a = s.direction;
    char b = c.controll(a);
    bool check = c.check_dir(a, b);

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
                v[i][j] = ' ';
            }
        }
    }
    //s.makeBon(s.head_x, s.head_y, a, check);
    s.Move(a);
    s.Draw(v, s.head_x, s.head_y, 3, a);
    s.direction = b;
    item(i);
    i++;
}

void Map::item(int count)
{
    if (count % 10 == 0)
    {
        random_device rd;
        mt19937 gen(rd());

        uniform_int_distribution<int> dis(1, 24);

        int a = dis(gen);
        int b = dis(gen);

        v[a][b] = '$';
        count = 0;
    }
}