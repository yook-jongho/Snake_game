class Map
{
public:
    char v[25][25] = {{'0'}}; //멥 배열
    void getMap(int l);       //map1.txt 받아옴
    void render();
    int level = 0;
    void upDate();
    void grow_item();  //item 멥에 표시해주는 함수
    void small_item(); //item 멥에 표시해주는 함수
    void potal();
    void levelUp(int score, int length, int plus, int minus);
    bool islevelup = false;
    bool gameOver;
};