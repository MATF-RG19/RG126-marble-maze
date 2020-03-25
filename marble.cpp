#include "marble.hpp"
#include "board.hpp"
#include <cmath>

#define MARBLEIN 1
#define MARBLEOUT 2
#define MARBLEIN_DEATH 3

void material(int i);

void MarbleBall::redraw(){
    //std::cout << "x: "<< x << " z: " << z << std::endl;

    glPushMatrix();
    if(x < 0 || x > BOARD_SIZE || y< 0 || y> BOARD_SIZE){
        marbleFall();
    }


        if (z < -1000){
            reset();
        }
        else {
            glTranslatef(x, y, z+50);
        }

        if (v_x != 0){
            glRotatef(x/5, 0, 1, 0);
        }
        else if (v_y != 0){
            glRotatef(-y/5, 1, 0, 0);
        }

        if(death == 0){
            material(MARBLEIN);
        }
        else{
            material(MARBLEIN_DEATH);
        }

            glutSolidSphere((MARBLE_SIZE/2),100,100);
        glColor3f(0, 1, 0);
        double life_upper[] = {0,0,1,(double)life/2};
        double life_downer[] = {0,0,-1,(double)life/2};
        glClipPlane(GL_CLIP_PLANE1, life_upper);
        glClipPlane(GL_CLIP_PLANE2, life_downer);
        glEnable(GL_CLIP_PLANE1);
        glEnable(GL_CLIP_PLANE2);
            material(MARBLEOUT);
            glutSolidSphere((MARBLE_SIZE/2)+0.2,100,100);
        glDisable(GL_CLIP_PLANE1);
        glDisable(GL_CLIP_PLANE2);
        glColor3f(1, 1, 1);



    glPopMatrix();
}



void MarbleBall::move(int direction){
    switch(direction) {
        case FWD:
            v_x = 0;
            v_y = (v_y < 0) ? 0 : v_y;
            v_y += ACCELERATION;
            v_y = v_y >= MAX_SPEED ? MAX_SPEED : v_y;
            y += v_y;
            break;
        case BACK:
            v_x = 0;
            v_y = (v_y > 0) ? 0 :  v_y;
            v_y -= ACCELERATION;
            v_y = v_y <= -MAX_SPEED ? -MAX_SPEED : v_y;
            y += v_y;
            break;
        case RIGHT:
            v_y = 0;
            v_x = (v_x < 0) ? 0 : v_x;
            v_x += ACCELERATION;
            v_x = v_x >= MAX_SPEED ? MAX_SPEED : v_x;
            x += v_x;
            break;
        case LEFT:
            v_y = 0;
            v_x = (v_x > 0) ? 0 : v_x;
            v_x -= ACCELERATION;
            v_x = v_x <= -MAX_SPEED ? -MAX_SPEED : v_x;
            x += v_x;
            break;
    }
}


void material(int i)
 {

    GLfloat mat_ambient[4];
    GLfloat mat_diffuse[4];
    GLfloat mat_specular[4];
    GLfloat shininess;

    switch (i) {
        case MARBLEOUT:
            mat_ambient[0] = 0.02;
            mat_ambient[1] = 0.17;
            mat_ambient[2] = 0.02;
            mat_ambient[3] = 0.55;

            mat_diffuse[0] = 0.07;
            mat_diffuse[1] = 0.61;
            mat_diffuse[2] = 0.07;
            mat_diffuse[3] = 0.55;

            mat_specular[0] = 0.6;
            mat_specular[1] = 0.72;
            mat_specular[2] = 0.6;
            mat_specular[3] = 0.5;
            shininess=76.8f;
            break;
        case MARBLEIN:
            shininess=30;

            mat_ambient[0] = 0.2;
            mat_ambient[1] = 0.2;
            mat_ambient[2] = 0.2;
            mat_ambient[3] = 1;

            mat_diffuse[0] = 0.1;
            mat_diffuse[1] = 0.1;
            mat_diffuse[2] = 0.1;
            mat_diffuse[3] = 1;

            mat_specular[0] = 0.6;
            mat_specular[1] = 0.7;
            mat_specular[2] = 0.6;
            mat_specular[3] =  0.5;
            shininess=76.8f;
            break;
        case MARBLEIN_DEATH:
            shininess=30;

            mat_ambient[0] = 0.17;
            mat_ambient[1] = 0.01;
            mat_ambient[2] = 0.01;
            mat_ambient[3] = 0.55;

            mat_diffuse[0] = 0.61;
            mat_diffuse[1] = 0.04;
            mat_diffuse[2] = 0.04;
            mat_diffuse[3] = 0.55;

            mat_specular[0] = 0.72;
            mat_specular[1] = 0.62;
            mat_specular[2] = 0.62;
            mat_specular[3] =  0.5;
            shininess=76.8f;
            break;
    }

	glMaterialf(GL_FRONT,GL_SHININESS,shininess);
	glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambient);
	glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse);
	glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
}

void MarbleBall::marbleFall(){
    if(x < 0){
        if(x  > -99){
            x-= 2;
            z =  sqrt(100*100 - x*x)-100;
        }
        else {
            v_z+=0.3;
            z -= v_z;
        }
    }
    if(x > BOARD_SIZE ){
        if( x < BOARD_SIZE+99){
            x+= 2;
            z =  sqrt(100*100 - (x-BOARD_SIZE)*(x-BOARD_SIZE))-100;
        }
        else {
            v_z+=0.3;
            z -= v_z;
        }
    }

    if(y < 0){
        if( y > -99){
            y-= 2;
            z =  sqrt(100*100 - y*y)-100;
        }
        else {
            v_z+=0.3;
            z -= v_z;
        }

    }
    if(y > BOARD_SIZE ){
        if( y < BOARD_SIZE+99){
            y+= 2;
            z =  sqrt(100*100 - (y-BOARD_SIZE)*(y-BOARD_SIZE))-100;
        }
        else{
            v_z+=0.3;
            z -= v_z;
        }
    }
    death = 1;

}
void MarbleBall::fallInHole(double distanceX, double distanceY){
    std::cout << "x:" << x << " y:"<< y << '\n';
    double y1;
    double x1;
    if(-distanceY < distanceX && distanceX < distanceY){
        y1=y;
        y -=1;
        x += (y-y1)*(distanceX/distanceY);
    }
    if(distanceY < distanceX && distanceX < -distanceY){
        y1=y;
        y += 1;
        x += (y-y1)*(distanceX/distanceY);
    }
    if(distanceX < distanceY && distanceY < -distanceX){
        x1=x;
        x +=1;
        y += (x-x1)*(distanceY/distanceX);
    }
    if(-distanceX < distanceY && distanceY < distanceX){
        x1=x;
        x -= 1;
        y += (x-x1)*(distanceY/distanceX);
    }
    std::cout << "x:" << x << " y:"<< y << '\n';
    std::cout << "dx:" << distanceX << " dy:"<< distanceY << '\n';
    v_z+=0.1;
    z -= v_z;
}
