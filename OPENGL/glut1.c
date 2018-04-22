// Exercises in computer graphics in OpenGL using C. The fourth semester of study.
// Tomasz Wisniewski
//
// GLUT Example with Matrix stack.
//
// NOTE: Compile with libraries :
// gcc glut1.c -lglaux -lglut32 -lglu32 -lopengl32 -std=c99 -pedantic

#include <stdio.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>
#include <Gl\gl.h>
#include <Gl\glu.h>
#include "GL\glut.h"

#define WINDOW_WIDTH 500
#define WINDOW_HEIGHT 500

double wsRadius = 0.1;
int wsSlices = 8;
int wsStacks = 8;
float angle = 0.0f;

float rgb[3] = { 1.0f, 1.0f, 1.0f };

/* Funkcje zwiazane z rysowanie na ekranie */
void display () {
    glClear(GL_COLOR_BUFFER_BIT);   /* Wyczyszczenie okna */
    glClear(GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();               /* Załadowanie macierzy jednostkowej */
    gluPerspective(45, 1, 1, 200);  /* Przygotowanie rzutowania perspektywicznego */
    glMatrixMode(GL_MODELVIEW);     /* Ustawienie macierzy modelowania */
    glLoadIdentity();               /* Załadowanie macierzy jednostkowej */

    // Przekształcenie sceny do widoku obserwatora
    glTranslatef(0, 0, -2.0f);

    // First sphere
    glPushMatrix();
    glColor3f(1.0f, 0 , 0); 
    glRotatef(angle, 1.0f, 0.0f, 0.0f);
    glutWireSphere(wsRadius, wsSlices, wsStacks);
    glPopMatrix();

    // Second sphere
    glPushMatrix();
    glColor3f(0, 1.0f , 0);  
    glRotatef(angle, 0, 1.0f, 0); 
    glTranslatef(0.3f, 0, 0);
    glutWireSphere(wsRadius, wsSlices, wsStacks);
    glPopMatrix();

    // Third sphere
    glPushMatrix();
    glColor3f(0, 0, 1.0f);   
    glRotatef(-angle, 0, 0, 1.0f); 
    glTranslatef(0.5f, 0, 0);
    glutWireSphere(wsRadius, wsSlices, wsStacks);
    
    // Fourth sphere - moon
    glPushMatrix();
    glColor3f(0, 0.5f, 0.5f);   
    glRotatef(angle, 0, 0, 1.0f); 
    glRotatef(angle, 0, 1.0f, 0); 
    glTranslatef(0.2f, 0, 0);
    glScalef(0.5f, 0.5f, 0.5f);
    glutWireSphere(wsRadius, wsSlices, wsStacks);
    glPopMatrix();

    glPopMatrix(); // Third sphere matrix

    angle -= 0.3f;
    if (angle >= 360.0f)
        angle = 0;
    else if (angle < 0)
        angle = 360.0f;

    glutSwapBuffers();
}

// Keyboard Input
void keyboardInput(unsigned char key, int x , int y) {
    switch(key) {
        case 27:
            exit(0);
            break;
        case 'q':
            wsStacks += 1;
            break;
        case 'w':
            wsStacks -= 1;
            break;
        case 'a':
            wsSlices += 1;
            break;
        case 's':
            wsSlices -= 1;
            break;
        case 'z':
            wsRadius += 0.02f;
            break;
        case 'x':
            wsRadius -= 0.02f;
            break;
        case 'r':
            break;
        case '1':
            break;
        default:
            break;
    }

}

void initGlut() {

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(0,0);
    glutCreateWindow("OPENGL + GLUT | ESC - quit | qw as zx - Controls");
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glutKeyboardFunc(keyboardInput); // keyboard input

    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutMainLoop();
}

int main(int argc , char **argv) {

    initGlut();

    return 0;
}
