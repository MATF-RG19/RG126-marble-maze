#ifndef __MARBLEBALL__
#define __MARBLEBALL__

#include <GL/glut.h>
#include <stdio.h>
#include <iostream>
#define FWD 1
#define LEFT 3
#define BACK 2
#define RIGHT 4
#define ACCELERATION 5
#define MAX_SPEED 100

class MarbleBall
{
public:
    int life;
    static MarbleBall* getInstance(){
        if(!instance){
            instance = new MarbleBall();
        }
        return instance;
    }

    ~MarbleBall();
    void redraw();
    //void reset();
    void move(int direction);

    double getX(){
        return x;
    }
    double getY(){
        return y;
    }
    double getZ(){
        return z;
    }

    void reset(){
        x = 0;
        y = 0;
        z = 50;
        v_x = 0;
        v_y = 0;
        v_z = 0;
        life = 100;
    }

private:
    static MarbleBall *instance;
    explicit MarbleBall(double x = 0, double y = 0, double z = 0, int life = 100)
      : life(life), x(x), y(y), z(z)
    {
        v_x = 0;
        v_y = 0;
        v_z = 0;
    }
    double x;
    double y;
    double z;
    double v_x;
    double v_y;
    double v_z;


};
#endif
