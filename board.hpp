#ifndef __BOARD__
#define __BOARD__


#include <GL/glut.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#define HOLE_NUM 100
#define LIFE_NUM 10

class Hole{
public:
    Hole(double x, double y, double size)
    : x(x), y(y), size(size)
    {
    }
    ~Hole();
    void draw();

private:
    double x;
    double y;
    double size;

};


class GetLife
{
public:
    GetLife(double x, double y)
    : x(x), y(y)
    {
    }
    ~GetLife();
    void draw();

private:
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


            GetLife *GetL = new GetLife(x*100+75, y*100+75);
            lifes.push_back(GetL);
        }
    }
    ~Board(){
        for(Hole* v : holes){
            delete v;
        }
    };
    void draw();
private:
    std::vector<Hole*> holes;
    std::vector<GetLife*> lifes;
};






#endif
