#ifndef __BOARD__
#define __BOARD__

#include <GL/glut.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#define HOLE_NUM 50
#define LIFE_NUM 10
#define BOARD_SIZE 2000


class Hole{
public:
    Hole(double x, double y, double size)
    : x(x), y(y), size(size)
    {
    }
    ~Hole();
    void draw();

    double x;
    double y;
    double size;

};

class FinishPoint{
public:
    FinishPoint(double x, double y)
    : x(x), y(y)
    {
    }
    ~FinishPoint();
    void draw();

    double x;
    double y;
};

class LifeToken
{
public:
    LifeToken(double x, double y)
    : x(x), y(y)
    {
    }
    ~LifeToken();
    void draw();

    double x;
    double y;
};


class Board{
public:
    Board(){

        int x;
        int y;
        srand (time(NULL));

        for(int i =0; i < HOLE_NUM; i++){
            x = rand()%(BOARD_SIZE/100-1);
            y = rand()%(BOARD_SIZE/100-1);

            if(x == (BOARD_SIZE/100-1) &&  y == (BOARD_SIZE/100-1))
                continue;

            if(freeHolePosition(x,y)){
                Hole *hole = new Hole(x*100+100, y*100+100, 100);
                holes.push_back(hole);
            }
            else {
                i--;
            }
        }

        for(int i =0; i < LIFE_NUM; i++){
            x = rand()%19;
            y = rand()%19;

            x = x*100+100;
            y = y*100+100;

            if(freeHolePosition(x,y)){
                LifeToken *GetL = new LifeToken(x, y);
                lifes.push_back(GetL);
            }
            else{
                i--;
            }

        }


        f = new FinishPoint(BOARD_SIZE-75,BOARD_SIZE-75);
    }
    ~Board(){
        for(Hole* v : holes){
            delete v;
        }
        for(LifeToken* lt : lifes){
            delete lt;
        }
    };
    void draw();
    void lifeMarbleCollision(); //proverava da li je kliker pokupio zivot
    void holeMarbleCollision(); //akcija je kliker upao u rupu
    void finishMarbleCollision(); //akcija ako je kliker stigao do cilja
    bool freeHolePosition(int x, int y);
private:
    std::vector<Hole*> holes;
    std::vector<LifeToken*> lifes;
    FinishPoint* f;
};






#endif
