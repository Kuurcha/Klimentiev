#include <GL/gl.h> 
#include <GL/glu.h>
#include <GL/glut.h>
#define SCREENSIZE 620
void reshape(int w, int h) 
{
    glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluOrtho2D(0, w, 0, h);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void display(void) { 
 GLfloat lp[4] = {1.5, 0.0, 2.0, 0}; 
 glEnable(GL_DEPTH_TEST);
 glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
 glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
 glEnable(GL_DEPTH_TEST);               
 glLightfv(GL_LIGHT0, GL_POSITION, lp); 
 glEnable(GL_LIGHT0);                   
 glEnable(GL_LIGHTING);                 
 glEnable(GL_COLOR_MATERIAL);           
 glEnable(GL_NORMALIZE);
	
 GLUquadricObj* QuadrObj;
 QuadrObj=gluNewQuadric();

 glViewport (0, 0, SCREENSIZE, (GLsizei) SCREENSIZE); 
 glMatrixMode (GL_PROJECTION);


 // Тело яйцо

 glLoadIdentity();			
 glTranslatef (0.1, 0.3, 0);		 
 glRotatef(25.0,0.0,0.0,-0.5);				
 glColor3f(0.921, 0.921,0.921);
 glScalef(1.5, 0.8, 0.7);    
 gluSphere(QuadrObj,0.2, 30, 30);

 //Ноги
 
 glLoadIdentity();
 glTranslatef (0.0,0.25, 0.0);
 glRotatef(90, 0.5,0.5,0.5);
 glRotatef(-45, 0.5, 0.5, 0.0);
 glScalef(0.1, 0.1, 0.1);
 glColor3f(0.8, 0.4, 0.0); 
 gluCylinder(QuadrObj,0.5,0.5,8.0,30,30);

 glLoadIdentity();
 glTranslatef (0.2,0.25, 0.0);
 glRotatef(90, 0.5,0.5,0.5);
 glRotatef(-45, 0.5, 0.5, 0.0);
 glScalef(0.1, 0.1, 0.1);
 glColor3f(0.8, 0.4, 0.0); 
 gluCylinder(QuadrObj,0.5,0.5,8.0,10,10);

 glColor3f(0.0, 0.0, 1);
 glBegin(GL_QUADS); 

        glColor3f(0.0f, 1.0f, 0.0f); // green
        glVertex3f(1.0f, 1.0f, -1.0f);
        glVertex3f(-1.0f, 1.0f, -1.0f);
        glVertex3f(-1.0f, 1.0f, 1.0f);
        glVertex3f(1.0f, 1.0f, 1.0f);

        // Bottom-face
        glColor3f(1.0f, 0.5f, 0.0f); // orange
        glVertex3f(1.0f, -1.0f, 1.0f);
        glVertex3f(-1.0f, -1.0f, 1.0f);
        glVertex3f(-1.0f, -1.0f, -1.0f);
        glVertex3f(1.0f, -1.0f, -1.0f);

        // Front-face
        glColor3f(1.0f, 0.0f, 0.0f); // red
        glVertex3f(1.0f, 1.0f, 1.0f);
        glVertex3f(-1.0f, 1.0f, 1.0f);
        glVertex3f(-1.0f, -1.0f, 1.0f);
        glVertex3f(1.0f, -1.0f, 1.0f);

        // Back-face
        glColor3f(1.0f, 1.0f, 0.0f); // yellow
        glVertex3f(1.0f, -1.0f, -1.0f);
        glVertex3f(-1.0f, -1.0f, -1.0f);
        glVertex3f(-1.0f, 1.0f, -1.0f);
        glVertex3f(1.0f, 1.0f, -1.0f);

        // Left-face
        glColor3f(0.0f, 0.0f, 1.0f); // blue
        glVertex3f(-1.0f, 1.0f, 1.0f);
        glVertex3f(-1.0f, 1.0f, -1.0f);
        glVertex3f(-1.0f, -1.0f, -1.0f);
        glVertex3f(-1.0f, -1.0f, 1.0f);

        // Right-face
        glColor3f(1.0f, 0.0f, 1.0f); // violet
        glVertex3f(1.0f, 1.0f, -1.0f);
        glVertex3f(1.0f, 1.0f, 1.0f);
        glVertex3f(1.0f, -1.0f, 1.0f);
        glVertex3f(1.0f, -1.0f, -1.0f);

        glTranslatef (0.2,1.5, 0.0);

 glEnd();

 //СТУПНИ 
//  GLUtesselator *feetLeft;
//  gluBeginPolygon(feetLeft); 
// 	gluTessVertex(feetLeft, 0.8);
 glutSwapBuffers();  
 glFlush(); 
} 



void main (int argc, char** argv) {  
    glutInit (&argc, argv);
    glutReshapeFunc(reshape);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition (50, 50); 
    glutInitWindowSize (620, 620);
    glutCreateWindow ("stork");

    glViewport (0, 0, (GLsizei) SCREENSIZE, (GLsizei) SCREENSIZE); 
    

    glClearColor (0.678, 0.807, 0.921, 0.);

    glutDisplayFunc(display); 
    glutMainLoop (); 
} 
