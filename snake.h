#include <ncurses.h>
#include <deque>
#include <vector>

using namespace std;
class Snake
{
public:
    int head_x = 13;
    int head_y = 13;
    int a[3] = {13, 14, 15};
    deque<int> body_x;
    deque<int> body_y;

    int tail_x, tail_y;
    int length = 3;
    char direction = 'l';
    void Draw(char v[][25], int x, int y, int len);

    void Move(char dir);
};
