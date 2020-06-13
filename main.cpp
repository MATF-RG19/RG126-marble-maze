#include <GL/glut.h>
#include <stdio.h>
#include <iostream>
#include <cstring>
#include <math.h>
#define PI 3.14f
#include "marble.hpp"
#include "board.hpp"
#include "image.h"


#define FILENAME0 "1.bmp"
#define FILENAME1 "win.bmp"
static GLuint names[2];

#define TIME_INTERVAL 500
#define TIME_INTERVAL_LIFE 20
#define TIME_INTERVAL_MOVE 20
#define TIMER_ID 1
#define TIMER_LIFE 2
#define TIMER_MOVE 3
#define LIFE_ANIMATION_MAX 2*360


static int game_start = 0;
int life_animation = 0;

int left=0;
int right=0;
int up=0;
int down=0;


/* Deklaracije callback funkcija. */
static void on_display(void);
static void on_keyboard(unsigned char key, int x, int y);
static void on_reshape(int width, int height);
static void on_keyReleased(unsigned char key,int x, int y);
void output(char *string);
static void on_timer(int value);

//funkcije
void camera();
void endScreen();

int holdOn = 0;
int i = 0;

static void texture_initialize();




MarbleBall* MarbleBall::instance = 0;
Board* board;

static int window_width = 1500, window_height = 700;




int main(int argc, char **argv)
{

    //kreinje podloge i klikera
    MarbleBall* ball = ball->getInstance();
    board = new Board();



    /* Inicijalizuje se GLUT. */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    /* Kreira se prozor. */
    glutInitWindowSize(window_width, window_height);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);


    glutIgnoreKeyRepeat(true);
    /* Registruju se callback funkcije. */
    glutDisplayFunc(on_display);
    glutKeyboardFunc(on_keyboard);
    glutReshapeFunc(on_reshape);
    glutKeyboardUpFunc(on_keyReleased);

    /* Obavlja se OpenGL inicijalizacija. */
     glClearColor(0.1, 0.1, 0.2, 0);
    glEnable(GL_DEPTH_TEST);

    texture_initialize();

    glutTimerFunc(TIME_INTERVAL_MOVE, on_timer, TIMER_MOVE);
    glutTimerFunc(TIME_INTERVAL_LIFE, on_timer, TIMER_LIFE);
    /* Program ulazi u glavnu petlju. */
    glutMainLoop();

    return 0;
}

//incijalizacija teksture
static void texture_initialize(){
    Image *image;


    glEnable(GL_TEXTURE_2D);

    glTexEnvf(GL_TEXTURE_ENV,
              GL_TEXTURE_ENV_MODE,
              GL_REPLACE);

    image = image_init(0, 0);

    /* Kreira se prva tekstura. */
    image_read(image, FILENAME0);

    glGenTextures(2, names);

    glBindTexture(GL_TEXTURE_2D, names[0]);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 image->width, image->height, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, image->pixels);

    image_read(image, FILENAME1);

    glBindTexture(GL_TEXTURE_2D, names[1]);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 image->width, image->height, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, image->pixels);


    /* Iskljucujemo aktivnu teksturu */
    glBindTexture(GL_TEXTURE_2D, 0);

    image_done(image);
}

//omogucavanje promene velicine prozora
static void on_reshape(int width, int height){

    window_width = width;
    window_height = height;
    glViewport(0,0,width,height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60,(float)width/height, 1, 2000);
}

//prilikom pritiska tastera za kretanje povecava se brzina kretanja
static void on_keyboard(unsigned char key, int x, int y){

    if(!game_start){
        glutTimerFunc(TIME_INTERVAL, on_timer, TIMER_ID);
        game_start = 1;
    }

    switch(key){
        case 27:
            exit(0);
            break;
        case 'W':
        case 'w':
            up=1;
            break;
        case 'A':
        case 'a':
            left=1;
            break;
        case 'S':
        case 's':
            down=1;
            break;
        case 'D':
        case 'd':
            right=1;
            break;
        case 'R':
        case 'r':
            {
                delete board;
                MarbleBall::getInstance()->reset();
                game_start = 0;
                board=new Board();
                break;
            }
    }
}

//prilikom oustanja tastera za kretanje smanjuje se brzina kretanja
static void on_keyReleased(unsigned char key, int x, int y){

    switch(key){
        case 'W':
        case 'w':
            up=0;
            break;
        case 'A':
        case 'a':
            left=0;
            break;
        case 'S':
        case 's':
            down=0;
            break;
        case 'D':
        case 'd':
            right=0;
            break;
    }
}


static void on_timer(int value)
{
    //tajmer funkcija
    if(value == TIMER_ID){
        if(MarbleBall::getInstance()->life == 0){
            MarbleBall::getInstance()->death = 1;
        }
        else{
            MarbleBall::getInstance()->life--;
        }
        if(holdOn==1){
            i++;
            if(i==14){
                holdOn=0;
                i=0;
            }
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

    if(value==TIMER_MOVE){
        //obogucavanje kretanja samo ako nije kraj igre
        if(MarbleBall::getInstance()->death==0 && MarbleBall::getInstance()->win==0
            && MarbleBall::getInstance()->moving == 1)
            MarbleBall::getInstance()->move(left,right,up,down);

        glutPostRedisplay();
        glutTimerFunc(TIME_INTERVAL_MOVE,on_timer,TIMER_MOVE);
    }


}

static void on_display(void)
{

    /* Pozicija svetla */
    GLfloat light_position[] = { 0, 0, 2000, 0 };
    /* Ambijentalna boja svetla. */
    GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1 };
    /* Difuzna boja svetla. */
    GLfloat light_diffuse[] = { 0.7, 0.7, 0.7, 1 };
    /* Spekularna boja svetla. */
    GLfloat light_specular[] = { 0.9, 0.9, 0.9, 1 };

    /* Brise se prethodni sadrzaj 'prozora'. */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    if(MarbleBall::getInstance()->end==1 ){
        endScreen();
    }else{

        camera();


        /* Ukljucuje se osvjetljenje i podesavaju parametri svetla. */
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        glLightfv(GL_LIGHT0, GL_POSITION, light_position);
        glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
        glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);


        glShadeModel(GL_SMOOTH);

        /*iscrtavanje klikera i  provera kolizija sa ostalim elementima*/
        MarbleBall::getInstance()->redraw();
        board->lifeMarbleCollision();
        board->holeMarbleCollision();
        board->finishMarbleCollision();
        board->teleportMarbleCollision();

        glDisable(GL_LIGHTING);
        glDisable(GL_LIGHT0);

        board->draw(names);


        /*ispis poena */
        char life_numb[10];
        char str_life[] = "Life: ";
        sprintf(life_numb, "%d", MarbleBall::getInstance()->life);
        strcat(str_life, life_numb);

        output(str_life);

    }

    /* Nova slika se salje na ekran. */
    glutSwapBuffers();
}

/*postavljanje teksture za kraj igre*/
void endScreen(){
    gluLookAt(0,0,-1,0,0,0,1,0,0);

     glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, names[1]);

        glBegin(GL_QUADS);
            glNormal3f(0, 0, 1);

            glTexCoord2f(0, 0);
            glVertex3f(-1, -1, 0);

            glTexCoord2f(1, 0);
            glVertex3f(-1, 1, 0);

            glTexCoord2f(1, 1);
            glVertex3f(1, 1, 0);

            glTexCoord2f(0, 1);
            glVertex3f(1, -1, 0);
        glEnd();



        glBindTexture(GL_TEXTURE_2D, 0);
    glPopMatrix();
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
