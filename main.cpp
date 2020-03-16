#include <GL/glut.h>
#include <stdio.h>
#include <iostream>
#include <cstring>
#include <math.h>
#define PI 3.14f
#include "marble.hpp"
#include "board.hpp"


#define TIME_INTERVAL 500
#define TIME_INTERVAL_LIFE 20
#define TIMER_ID 1
#define TIMER_LIFE 2
#define LIFE_ANIMATION_MAX 2*360

static int gravity_on = 0;
static int game_start = 0;
int life_animation = 0;


/* Deklaracije callback funkcija. */
static void on_display(void);
static void on_keyboard(unsigned char key, int x, int y);
static void on_reshape(int width, int height);
void output(char *string);
//void drawText(const char *text, int length, int x, int y);
//static void on_keyReleased(unsigned char key , int x , int y);
static void on_timer(int value);

//funkcije
void marble(double x, double y, double z);
void plain();
void camera();
void end();

void move(int direction);

MarbleBall* MarbleBall::instance = 0;
Board* board;

static int window_width = 1500, window_height = 700;

float x=0;
float y=0;
float speed=1;


int main(int argc, char **argv)
{


    MarbleBall* ball = ball->getInstance();
    board = new Board;

    /* Inicijalizuje se GLUT. */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    /* Kreira se prozor. */
    glutInitWindowSize(window_width, window_height);
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

    glutTimerFunc(TIME_INTERVAL_LIFE, on_timer, TIMER_LIFE);
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

    if(!game_start){
        std::cout << "t" << std::endl;
        glutTimerFunc(TIME_INTERVAL, on_timer, TIMER_ID);
        game_start = 1;
    }

    switch(key){
        case 27:
            exit(0);
            break;
        case 'W':
        case 'w':
            MarbleBall::getInstance()->move(FWD);
            game_start = 1;
            break;
        case 'A':
        case 'a':
            MarbleBall::getInstance()->move(LEFT);
            game_start = 1;
            break;
        case 'S':
        case 's':
            MarbleBall::getInstance()->move(BACK);
            game_start = 1;
            break;
        case 'D':
        case 'd':
            MarbleBall::getInstance()->move(RIGHT);
            game_start = 1;
            break;
        case 'R':
        case 'r':
            {
                MarbleBall::getInstance()->reset();
                game_start = 0;
                break;
            }
    }



    glutPostRedisplay();
}



static void on_timer(int value)
{
    //tajmer funkcija
    if(value == TIMER_ID){
        MarbleBall::getInstance()->life--;
        std::cout << MarbleBall::getInstance()->life<< std::endl;
        if(MarbleBall::getInstance()->life == 0){
            //TODO game endi
        }
        glutPostRedisplay();
        if(game_start){

            glutTimerFunc(TIME_INTERVAL, on_timer, TIMER_ID);
        }
    }


    if(value == TIMER_LIFE){
            if(life_animation < 360){
                life_animation += 1;
            }
            else{
                life_animation = 0;
            }
            glutPostRedisplay();
            glutTimerFunc(TIME_INTERVAL_LIFE, on_timer, TIMER_LIFE);
    }


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

    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);

    board->draw();



    char life_numb[10];
    char str_life[] = "Life: ";
    sprintf(life_numb, "%d", MarbleBall::getInstance()->life);
    strcat(str_life, life_numb);


    // glDisable(GL_LIGHTING);
	 	output(str_life);
    // glEnable(GL_LIGHTING);



    /* Nova slika se salje na ekran. */
    glutSwapBuffers();
}

void camera(){
    //pozicioniranje kamere
    gluLookAt( MarbleBall::getInstance()->getX(),
              MarbleBall::getInstance()->getY()-600,
              900,
              MarbleBall::getInstance()->getX(),
              MarbleBall::getInstance()->getY(),
              MarbleBall::getInstance()->getZ(),
              0,0,1);
}



void output(char *string) {
	//funkcija ispisuje trenutni zivot u gorenjm levom uglu

	glColor3f( 1.0, 1.0, 1.0 );
	glMatrixMode( GL_PROJECTION );

	glPushMatrix();
		glLoadIdentity();
		gluOrtho2D( 0, window_width, 0, window_height );

		glMatrixMode( GL_MODELVIEW );

		glPushMatrix();
			glLoadIdentity();

			glRasterPos2i( 10, window_height-10-24 ); // wh - offset - fontsize

			int len = (int)strlen(string);
			for ( int i = 0; i<len; ++i ) {

				glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
			}
		glPopMatrix();

		glMatrixMode( GL_PROJECTION );
	glPopMatrix();

	glMatrixMode( GL_MODELVIEW );

}
