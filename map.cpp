#include <fstream>
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

void Map::render()
{

    initscr();
    resize_term(60, 100);

    border('+', '+', '+', '+', '*', '*', '*', '*');
    refresh();

    mvprintw(2, 2, "<snake game>");

    WINDOW *win1;
    win1 = newwin(25, 25, 3, 3);
    //mvwprintw(win1, 1, 1, "A new window");
    //wborder(win1, '@', '@', '@', '@', '@', '@', '@', '@');

    for (int i = 0; i < 25; i++)
    {
        for (int j = 0; j < 25; j++)
        {
            wprintw(win1, "%c", v[i][j]);
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
    char a = c.controll('l');
    s.Move(a);
    s.Draw(v, s.head_x, s.head_y, 3, a);

    wrefresh(win1);
    //inner box
    //s.Move(14);
    delwin(win1);
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