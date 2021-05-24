#include <ncurses.h>
#include <locale.h> // 혹은 <locale.h>
#include <iostream>
int main()
{
        setlocale(LC_ALL, "");

        initscr();
        resize_term(60, 100);

        border('|', '|', '+', '+', '*', '*', '*', '*');
        mvprintw(2, 10, "<SNAKE GAME>");

        //inner box
        WINDOW *snake_win = subwin(stdscr, 25, 25, 3, 3);
        wborder(snake_win, '+', '+', '+', '+', '*', '*', '*', '*');
        mvprintw(14, 14, "@OO");

        WINDOW *win1 = subwin(stdscr, 10, 20, 4, 60);
        box(win1, 0, 0);
        mvprintw(5, 61, "Score Board");

        refresh();
        getch();
        delwin(win1);
        delwin(snake_win);
        endwin();
        return 0;
}
