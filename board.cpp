#include "board.hpp"
#include "marble.hpp"
#include <math.h>
#include <iostream>
#define PI 3.14f
extern int life_animation;
#define LIFE_SIZE 75


void Board::draw(){
    glPushMatrix();
        glColor3f(0.5,0.5,0.5);
        glTranslatef(BOARD_SIZE/2,BOARD_SIZE/2,0);
        glScaled(BOARD_SIZE,BOARD_SIZE,1);
        glutSolidCube(1);
    glPopMatrix();

    for(Hole* v:holes){
        v->draw();
    }

    for(LifeToken* g:lifes){
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

void LifeToken::draw(){
    float ugao =0;
    //std::cout << life_animation << "*" << std::endl;
    glPushMatrix();
        glColor3f(0.1,0.5,0.1);

        glTranslatef(x,y,50);

        glPushMatrix();
            glRotatef(30, 0,1,0);
            glBegin(GL_LINE_STRIP);
            glNormal3f(0,0,1);
            while(ugao < 2*PI+0.01){
                glVertex3f(cos(ugao)*(LIFE_SIZE/2), sin(ugao)*(LIFE_SIZE/2), 0);
                ugao += PI/32;
            }
            glEnd();
                glTranslatef((LIFE_SIZE/2)*cos(life_animation*2*PI/360.0),(LIFE_SIZE/2)*sin(life_animation*2*PI/360.0),0);
                glutSolidSphere((LIFE_SIZE/10),32,32);
        glPopMatrix();

        glPushMatrix();
            glRotatef(120, 0,1,0);
            glBegin(GL_LINE_STRIP);
            glNormal3f(0,0,1);
            ugao = 0;
            while(ugao < 2*PI+0.01){
                glVertex3f((LIFE_SIZE/2)*cos(ugao), (LIFE_SIZE/2)*sin(ugao), 0);
                ugao += PI/32;
            }
            glEnd();
                glTranslatef((LIFE_SIZE/2)*cos((life_animation+240)*2*PI/360.0),(LIFE_SIZE/2)*sin((life_animation+240)*2*PI/360.0),0);
                glutSolidSphere((LIFE_SIZE/10),32,32);
        glPopMatrix();

        glPushMatrix();
            glBegin(GL_LINE_STRIP);
            glNormal3f(0,0,1);
            ugao = 0;
            while(ugao < 2*PI+0.01){
                glVertex3f(cos(ugao)*(LIFE_SIZE/2), sin(ugao)*(LIFE_SIZE/2), 0);
                ugao += PI/32;
            }
            glEnd();
            glTranslatef((LIFE_SIZE/2)*cos((life_animation+120)*2*PI/360.0),(LIFE_SIZE/2)*sin((life_animation+120)*2*PI/360.0),0);
            glutSolidSphere((LIFE_SIZE/10),32,32);
        glPopMatrix();

    glPopMatrix();
}

void Board::lifeMarbleCollision(){

    for( unsigned i = 0; i< lifes.size(); i++){
        if(abs(lifes[i]->x - MarbleBall::getInstance()->getX())<MARBLE_SIZE/2 &&
           abs(lifes[i]->y - MarbleBall::getInstance()->getY())<MARBLE_SIZE/2
        ){
            MarbleBall::getInstance()->life += 20;
            lifes.erase(std::cbegin(lifes)+i);
        }


    }
}


void Board::holeMarbleCollision(){

    for(Hole* h : holes){
        if(abs(h->x - MarbleBall::getInstance()->getX())<MARBLE_SIZE/2.1 &&
           abs(h->y - MarbleBall::getInstance()->getY())<MARBLE_SIZE/2.1
        ){
             MarbleBall::getInstance()->life = 0;
        }
    }
}
