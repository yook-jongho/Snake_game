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

    vector<int> bon;
    vector<char> bondir;
    int tail_x, tail_y;
    int length = 2;
    char direction = 'l';
    int position_x, position_y;
    void Draw(char v[][25], int x, int y, int len);

    //void Controll(char v[][25], int x, int y);
    void makeBon(int x, int y, char dir);
    void removeBon();

    void Move(char dir);
};
