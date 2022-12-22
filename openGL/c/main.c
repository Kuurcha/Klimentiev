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

void drawCube(){
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
 glColor3f(0.933, 0.933, 0.933); 
 glRotatef(45, -1, 1, 0);
 glScalef(1.8, 1.0, 0.6);
 glTranslatef (0.0,0.5, 0.0);
 gluSphere(QuadrObj,0.2, 20, 20);
 //Ноги
 
 glLoadIdentity();
 glColor3f(0.8, 0.4, 0.0); 
 glTranslatef (0.0, 0.5, 0.0);
 glScalef(0.1, 0.13, 0.1);
 glRotatef(90, 1, 1, 1);
 glRotatef(-50, 1, 1, 0);
 gluCylinder(QuadrObj,0.5,0.5,16.0,30,30);

 glLoadIdentity();
 glTranslatef (0.25, -0.27, 0.0);
 glColor3f(0.8, 0.4, 0.0); 
 glScalef(1.0, 0.3, 1.0);
 glRotatef(25, 0.0,0.5,0.5);
 glutSolidCube(0.2);

 
 glLoadIdentity();
 glColor3f(0.8, 0.4, 0.0); 
 glTranslatef (-0.2, 0.5, 0.0);
 glScalef(0.1, 0.13, 0.1);
 glRotatef(90, 1, 1, 1);
 glRotatef(-50, 1, 1, 0);
 gluCylinder(QuadrObj,0.5,0.5,16.0,30,30);

 glLoadIdentity();
 glTranslatef (0.05, -0.27, 0.0);
 glColor3f(0.8, 0.4, 0.0); 
 glScalef(1.0, 0.3, 1.0);
 glRotatef(25, 0.0,0.5,0.5);
 glutSolidCube(0.2);

 //шея
 glLoadIdentity();
 glColor3f(0.933, 0.933, 0.933); 
 glTranslatef (-0.4, 0.8, 0.5);
 glScalef(0.2, 0.2, 0.2);
 glRotatef(90, 1, 1, 1);
 glRotatef(-50, 1, 1, 0);
 gluCylinder(QuadrObj,0.35,0.4,5.0,30,30);


 //голова
 glLoadIdentity();
 glColor3f(0.933, 0.933, 0.933); 
 glScalef(1.1, 0.8, 1.0);
 glTranslatef (-0.33, 1.05, 0.5);
 glRotatef(-30, 0, 1, 1);
 glutSolidSphere(0.2, 30, 30);
 
 glLoadIdentity();
 glColor3f(0.8, 0.4, 0.0);
 glTranslatef (-0.40, 0.80, 0.3);
 glRotatef(-90, 0, 1, -1);
 
 glRotatef(-80, 1, 1, 0);
 glutSolidCone(0.05, 0.4, 30, 30);


 //глаза

 glLoadIdentity();
 glColor3f(1, 1, 1);
 glTranslatef (-0.3, 0.85, 0.0);
 glutSolidSphere(0.05, 30, 30);
 glutSwapBuffers();  

  glLoadIdentity();
 glColor3f(1, 1, 1);
 glTranslatef (-0.5, 0.85, -0.7);
 glutSolidSphere(0.05, 30, 30);


//крылья

  glLoadIdentity();
  glColor3f(0.933, 0.933, 0.933);
  glTranslatef (0.5, 0.5, 0.0); 
  glScalef(2.0, 0.4, 0.5);
  glRotatef(135, 1, 1, 1);
  glutSolidCube(0.4);

  glLoadIdentity();
  glColor3f(0.933, 0.933, 0.933);
  glTranslatef (-0.55, 0.4, 0.1); 
  glScalef(2.0, 0.4, 0.5);
  glRotatef(135, 1, 1, 1);
  glRotatef(12, 0, 1, 1);
  glutSolidCube(0.4);
  
  glLoadIdentity();
  glColor3f(0.5333, 0.364, 0.682); 
  glTranslatef (-0.1, -0.03, 0.5); 
  glScalef(0.8, 1.5, 1.0);
  glRotatef(90, 1, 1, 1);
  glRotatef(-50, 1, 1, 0);
  gluCylinder(QuadrObj,0.5,0.5,0.12,30,30);


  //Ребенок

 glLoadIdentity(); 
 glColor3f(0.970, 0.970, 0.970); 
 glTranslatef (-0.1,-0.5, 0.0);
 glRotatef(45, -1, 1, 1);
 glScalef(1.2, 0.69, 0.6);

 gluSphere(QuadrObj,0.25, 20, 20);

 glLoadIdentity(); 
 glColor3f(0.886, 0.721, 0.705); 
 glTranslatef (-0.16, -0.48, -0.3);
 glRotatef(78, 0, 1, 1);
 glScalef(0.5, 1.0, 1.0);

 gluSphere(QuadrObj,0.1, 20, 20);


    //глаза ребенка

     //глаза

 glLoadIdentity();

 glColor3f(1, 1, 1);
 glTranslatef (-0.22, -0.46, -0.5);
 glRotatef(78, 0, 1, 1);
 glutSolidSphere(0.02, 30, 30);

 glLoadIdentity();
 glColor3f(1, 1, 1);
 glTranslatef (-0.11, -0.51, -0.5);
  glRotatef(78, 0, 1, 1);
 glutSolidSphere(0.02, 30, 30);

    //соска
    glLoadIdentity();
    glColor3f(0.1, 0.1, 0.8);
        glTranslatef (-0.1, -0.41, -0.3);
    glRotatef(90, 0, -1, 1);


    glutSolidCone(0.05, 0.2, 30, 30);


 glutSwapBuffers();  
 glFlush(); 
} 



void main (int argc, char** argv) {  
    glutInit (&argc, argv);
    glutReshapeFunc(reshape);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition (50, 50); 
    glutInitWindowSize (620, 620);
    glutCreateWindow ("stork with a child");

    glViewport (0, 0, (GLsizei) SCREENSIZE, (GLsizei) SCREENSIZE); 
    

    glClearColor (0.678, 0.807, 0.921, 0.);

    glutDisplayFunc(display); 
    glutMainLoop (); 
} 
