#include "marble.hpp"

void MarbleBall::redraw(){
    glPushMatrix();
        glColor3f(0, 0, 0);
        if (z < -3000){
            reset();
        }
        else {
            glTranslatef(x, y, z);
        }

        if (v_x != 0){
            glRotatef(x, 0, 1, 0);
        }
        else if (v_y != 0){
            glRotatef(-y, 1, 0, 0);
        }
        glutSolidSphere(50,100,100);
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
