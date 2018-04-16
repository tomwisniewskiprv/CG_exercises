// Exercises in computer graphics in OpenGL using C. The fourth semester of study.
// Tomasz Wisniewski
// Example of AUX in OpenGL
// 
// NOTE: Compile with libraries :
// gcc aux1.c -lglaux -lglut32 -lglu32 -lopengl32 -std=c99 -pedantic


#include <stdio.h>
#include <time.h>
#include <math.h>
#include <Gl\gl.h>
#include <Gl\glu.h>
#include "GL\glut.h"
#include "Gl\glaux.h"

#define WINDOW_WIDTH 500
#define WINDOW_HEIGHT 500
#define SIDE 100
#define STEP 1.0f       // move step
#define STEP_A 0.2f     // angle step

float random_float() {
      return (float)rand()/(float)RAND_MAX;
}

struct square {
    float x , y , angle;
    float r , g , b;
    float diagonal;
    float half_side;
    float border;

} quad;


void random_rgb(struct square *s) {
    s->r = random_float();
    s->g = random_float();
    s->b = random_float();
}

void update_quad() {
	
    // Check position
    if (quad.x <= (WINDOW_WIDTH - SIDE) && quad.y <= 0 ) {
		quad.x += STEP;
	} else if (quad.x >= (WINDOW_WIDTH - SIDE) && quad.y < (WINDOW_WIDTH - SIDE)) {
		quad.y += STEP;		
	} else if ( quad.x >= 0 && quad.y >= (WINDOW_WIDTH - SIDE)) {
		quad.x-= STEP;
	} else if ( quad.x <= 0 && quad.y >= 0) {
		quad.y-= STEP;
	}

    // Updated angle
    quad.angle += STEP_A;

    // Change color in corners
    if (quad.x == 0 && quad.y == 0 ||
        quad.x == (WINDOW_WIDTH - SIDE) && quad.y == 0 ||
        quad.x == (WINDOW_WIDTH - SIDE) && quad.y == (WINDOW_WIDTH - SIDE) ||
        quad.x == 0 && quad.y == (WINDOW_WIDTH - SIDE))
        
        random_rgb(&quad); 
}

/* Funkcje zwiazane z rysowanie na ekranie */
void CALLBACK display() {

    glClear(GL_COLOR_BUFFER_BIT);   /* Wyczyszczenie okna */
    glMatrixMode(GL_MODELVIEW);     /* Ustawienie macierzy modelowania */
    glLoadIdentity();               /* Załadowanie macierzy jednostkowej */

    glClear(GL_COLOR_BUFFER_BIT);

    glTranslatef(quad.x, quad.y, 0);
    glPushMatrix();

    glTranslatef(quad.half_side, quad.half_side, 0.0);
    glScalef(0.7, 0.7 , 0);
    glRotatef(quad.angle, 0.0f, 0.0f, 1.0f); 
    glTranslatef(quad.diagonal, quad.diagonal, 0.0);
    glTranslatef(-quad.border, -quad.border, 0.0);

    glColor3f(quad.r , quad.g , quad.b);    /* Ustalenie koloru obiektu */
    glBegin(GL_POLYGON);                    /* Narysowanie obiektu */
        glVertex2i(0,0); glVertex2i(0,SIDE);
        glVertex2i(SIDE,SIDE); glVertex2i(SIDE,0);
    glEnd();

    glPopMatrix();
    auxSwapBuffers();
    
    update_quad();
}


/* Zakonczenie pracy */
void CALLBACK key_esc() {
    auxQuit(); 
}

/* Losowy kolor */
void CALLBACK key_q() {
    random_rgb(&quad);
}

int main() {

    // Init
    quad.diagonal = (sqrt(2) * SIDE ) - SIDE;
    quad.half_side = SIDE / 2;
    quad.border = quad.diagonal + quad.half_side;
    random_rgb(&quad); 

    // AUX
    auxInitDisplayMode(AUX_DOUBLE | AUX_RGBA);
    auxInitPosition(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    auxInitWindow("Open GL - aux1 , ESC - quit , q - change color");
    auxKeyFunc(AUX_ESCAPE, key_esc);
    auxKeyFunc(AUX_q, key_q);

    auxIdleFunc(display);
    auxMainLoop(display);

    return 0;
}
