#include <ncurses.h>
class Controll
{
public:
    char controll(char dir);
    bool check_dir(char dir1, char dir2);
    bool check_wall(int x, int y);
    bool check_item(int x, int y, int a, int b);
};