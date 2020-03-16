#include "board.hpp"
#include <math.h>
#include <iostream>
#define PI 3.14f
extern int life_animation;


void Board::draw(){
    glPushMatrix();
        glColor3f(0.5,0.5,0.5);
        glTranslatef(1000,1000,0);
        glScaled(2000,2000,1);
        glutSolidCube(1);
    glPopMatrix();

    for(Hole* v:holes){
        v->draw();
    }

    for(GetLife* g:lifes){
        g->draw();
    }

}

void Hole::draw(){
    float ugao =0;
    glPushMatrix();
        glColor3f(0.5,0,0.5);
        glBegin(GL_POLYGON);
        glNormal3f(0,0,1);
        while(ugao < 2*PI+0.01){
            glVertex3f(cos(ugao)*size/2+x, sin(ugao)*size/2+y, 1);
            ugao += PI/32;
        }
        glEnd();
    glPopMatrix();

}

void GetLife::draw(){
    float ugao =0;
    std::cout << life_animation << "*" << std::endl;
    // glPushMatrix();
    //     glColor3f(0.1,0.5,0.1);
    //
    //     glTranslatef(x,y,50);
    //
    //     glPushMatrix();
    //         glRotatef(30, 0,1,0);
    //         glBegin(GL_LINE_STRIP);
    //         glNormal3f(0,0,1);
    //         while(ugao < 2*PI+0.01){
    //             glVertex3f(cos(ugao)*50, sin(ugao)*50, 0);
    //             ugao += PI/32;
    //         }
    //         glEnd();
    //             glTranslatef(50*cos(life_animation*2*PI/360.0),50*sin(life_animation*2*PI/360.0),0);
    //             glutSolidSphere(10,32,32);
    //     glPopMatrix();
    //
    //     glPushMatrix();
    //         glRotatef(120, 0,1,0);
    //         glBegin(GL_LINE_STRIP);
    //         glNormal3f(0,0,1);
    //         ugao = 0;
    //         while(ugao < 2*PI+0.01){
    //             glVertex3f(cos(ugao)*50, sin(ugao)*50, 0);
    //             ugao += PI/32;
    //         }
    //         glEnd();
    //             glTranslatef(50*cos((life_animation+240)*2*PI/360.0),50*sin((life_animation+240)*2*PI/360.0),0);
    //             glutSolidSphere(10,32,32);
    //     glPopMatrix();
    //
    //     glPushMatrix();
    //         glBegin(GL_LINE_STRIP);
    //         glNormal3f(0,0,1);
    //         ugao = 0;
    //         while(ugao < 2*PI+0.01){
    //             glVertex3f(cos(ugao)*50, sin(ugao)*50, 0);
    //             ugao += PI/32;
    //         }
    //         glEnd();
    //         glTranslatef(50*cos((life_animation+120)*2*PI/360.0),50*sin((life_animation+120)*2*PI/360.0),0);
    //         glutSolidSphere(10,32,32);
    //     glPopMatrix();


    //glPopMatrix();

}
