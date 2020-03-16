#include "marble.hpp"
#define MARBLEIN 1
#define MARBLEOUT 2

void material(int i);

void MarbleBall::redraw(){
    glPushMatrix();
        if (z < -3000){
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

            material(MARBLEIN);
            glutSolidSphere(50,100,100);
        glColor3f(0, 1, 0);
        double life_upper[] = {0,0,1,life/2};
        double life_downer[] = {0,0,-1,life/2};
        glClipPlane(GL_CLIP_PLANE1, life_upper);
        glClipPlane(GL_CLIP_PLANE2, life_downer);
        glEnable(GL_CLIP_PLANE1);
        glEnable(GL_CLIP_PLANE2);
            material(2);
            glutSolidSphere(50.2,100,100);
        glDisable(GL_CLIP_PLANE1);
        glDisable(GL_CLIP_PLANE2);
        glColor3f(1, 1, 1);

            //glutWireSphere(51, 10,10);

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
    }



	glMaterialf(GL_FRONT,GL_SHININESS,shininess);
	glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambient);
	glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse);
	glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);



}
