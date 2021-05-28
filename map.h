class Map
{
public:
    char v[25][25] = {{'0'}}; //멥 배열

    void getMap(); //map1.txt 받아옴
    bool render();
    void upDate();
    void item(); //item 멥에 표시해주는 함수
};