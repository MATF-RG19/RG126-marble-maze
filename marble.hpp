#ifndef __MARBLEBALL__
#define __MARBLEBALL__

#include <GL/glut.h>
#include <stdio.h>
#include <iostream>
#define ACCELERATION 0.4
#define BRAKING 0.5
#define MAX_SPEED 20
#define MARBLE_SIZE 100

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
    void move(int left, int right, int up, int down);

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
        death = 0;
        win = 0;
    }
    void marbleFall();
    void fallInHole(double distanceX, double distanceY);
    void marbleWin();
    int death;
    int win;

private:
    static MarbleBall *instance;
    explicit MarbleBall(double x = 0, double y = 0, double z = 0, int life = 100)
      : life(life), x(x), y(y), z(z)
    {
        death = 0;
        win = 0;
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
