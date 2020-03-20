#ifndef __BOARD__
#define __BOARD__

#include <GL/glut.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#define HOLE_NUM 100
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
        for(int i =0; i < HOLE_NUM; i++){
            x = rand()%19;
            y = rand()%19;

            Hole *hole = new Hole(x*100+75, y*100+75, 100);
            holes.push_back(hole);
        }

        for(int i =0; i < LIFE_NUM; i++){
            x = rand()%19;
            y = rand()%19;


            LifeToken *GetL = new LifeToken(x*100+75, y*100+75);
            lifes.push_back(GetL);
        }
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
    void lifeMarbleCollision();
    void holeMarbleCollision();

private:
    std::vector<Hole*> holes;
    std::vector<LifeToken*> lifes;
};






#endif
