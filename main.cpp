#include <GL/glut.h>
#include <stdio.h>
#include <iostream>
#include "marble.hpp"


static int gravity_on = 0;

/* Deklaracije callback funkcija. */
static void on_display(void);
static void on_keyboard(unsigned char key, int x, int y);
static void on_reshape(int width, int height);
//static void on_keyReleased(unsigned char key , int x , int y);
static void on_timer(int value);

//funkcije
void marble(double x, double y, double z);
void plain();
void camera();
void end();

void move(int direction);

MarbleBall* MarbleBall::instance = 0;

static int window_width, window_height;
float x=0;
float y=0;
float speed=1;

void applyAcc(double amp, int x, int y, int z)
{

}

int main(int argc, char **argv)
{

    MarbleBall* ball = ball->getInstance();

    /* Inicijalizuje se GLUT. */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    /* Kreira se prozor. */
    glutInitWindowSize(1500, 700);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);



    /* Registruju se callback funkcije. */
    glutDisplayFunc(on_display);
    glutKeyboardFunc(on_keyboard);
    glutReshapeFunc(on_reshape);
    //glutKeyboardUpFunc(on_keyReleased);

    /* Obavlja se OpenGL inicijalizacija. */
    glClearColor(0.75, 0.75, 0.75, 0);
    glEnable(GL_DEPTH_TEST);

    /* Program ulazi u glavnu petlju. */
    glutMainLoop();

    return 0;
}

static void on_reshape(int width, int height){


    window_width = width;
    window_height = height;
    glViewport(0,0,width,height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60,(float)width/height, 1, 2000);
}


static void on_keyboard(unsigned char key, int x, int y){
    switch(key){
        case 27:
            exit(0);
            break;
        case 'W':
        case 'w':
            MarbleBall::getInstance()->move(FWD);
            break;
        case 'A':
        case 'a':
            MarbleBall::getInstance()->move(LEFT);
            break;
        case 'S':
        case 's':
            MarbleBall::getInstance()->move(BACK);
            break;
        case 'D':
        case 'd':
            MarbleBall::getInstance()->move(RIGHT);
            break;
        case 'R':
        case 'r':
            {
                MarbleBall::getInstance()->reset();
                break;
            }

    }

    glutPostRedisplay();
}



static void on_timer(int value)
{

}

static void on_display(void)
{
    /* Pozicija svetla (u pitanju je direkcionalno svetlo). */
    GLfloat light_position[] = { 0, 0, 2000, 0 };

    /* Ambijentalna boja svetla. */
    GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1 };

    /* Difuzna boja svetla. */
    GLfloat light_diffuse[] = { 0.7, 0.7, 0.7, 1 };

    /* Spekularna boja svetla. */
    GLfloat light_specular[] = { 0.9, 0.9, 0.9, 1 };

    /* Koeficijenti ambijentalne refleksije materijala. */
    GLfloat ambient_coeffs[] = { 1.0, 0.1, 0.1, 1 };

    /* Koeficijenti difuzne refleksije materijala. */
    GLfloat diffuse_coeffs[] = { 0.0, 0.0, 0.0, 1 };

    /* Koeficijenti spekularne refleksije materijala. */
    GLfloat specular_coeffs[] = { 1, 1, 1, 1 };

    /* Koeficijent glatkosti materijala. */
    GLfloat shininess = 20;





    /* Brise se prethodni sadrzaj 'prozora'. */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    camera();


    /* Ukljucuje se osvjetljenje i podesavaju parametri svetla. */
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    /* Podesavaju se parametri materijala. */
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular_coeffs);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);


    glShadeModel(GL_SMOOTH);
    MarbleBall::getInstance()->redraw();

    glPushMatrix();
        glColor3f(1,0,0);
        glutSolidSphere(10,10,10);
    glPopMatrix();

    glPushMatrix();
        glColor3f(1,0,0);
        glTranslatef(100,300,0);
        glutSolidSphere(10,10,10);
    glPopMatrix();



    glPushMatrix();
        glColor3f(0.5,0.5,0);
        glTranslatef(1000,1000,-50);
        glScaled(2000,2000,1);
        glutSolidCube(1);
    glPopMatrix();




    /* Nova slika se salje na ekran. */
    glutSwapBuffers();
}

void camera(){

    gluLookAt( MarbleBall::getInstance()->getX(),
              MarbleBall::getInstance()->getY()-600,
              900,
              MarbleBall::getInstance()->getX(),
              MarbleBall::getInstance()->getY(),
              MarbleBall::getInstance()->getZ(),
              0,0,1);
}
