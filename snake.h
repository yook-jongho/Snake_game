#include <ncurses.h>

class Snake
{
public:
    char direction;
    int position_x, position_y;
    void init_pos(char v[][25]);
    void Move(char v[][25], int x, int y);
};