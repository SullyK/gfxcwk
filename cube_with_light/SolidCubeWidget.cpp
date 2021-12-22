#include <GL/glu.h>
#include <QGLWidget>
#include "SolidCubeWidget.h"
#include<iostream>

// Setting up material properties
typedef struct materialStruct {
  GLfloat ambient[4];
  GLfloat diffuse[4];
  GLfloat specular[4];
  GLfloat shininess;
} materialStruct;


static materialStruct brassMaterials = {
  { 0.33, 0.22, 0.03, 1.0},
  { 0.78, 0.57, 0.11, 1.0},
  { 0.99, 0.91, 0.81, 1.0},
  27.8 
};

static materialStruct whiteShinyMaterials = {
  { 1.0, 1.0, 1.0, 1.0},
  { 1.0, 1.0, 1.0, 1.0},
  { 1.0, 1.0, 1.0, 1.0},
  100.0 
};


// constructor
SolidCubeWidget::SolidCubeWidget(QWidget *parent)
	: QGLWidget(parent)
	{ // constructor
       

	} // constructor

// called when OpenGL context is set up
void SolidCubeWidget::initializeGL()
	{ // initializeGL()
	// set the widget background colour
	glClearColor(0.3, 0.3, 0.3, 0.0);
	

 
	} // initializeGL()


// called every time the widget is resized
void SolidCubeWidget::resizeGL(int w, int h)
	{ // resizeGL()
	// set the viewport to the entire widget
	glViewport(0, 0, w, h);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
   
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
    GLfloat light_pos[] = {100., 100., 100., 1.};
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    glLightf (GL_LIGHT0, GL_SPOT_CUTOFF,15.);


                                                                                                                                                               
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-10.0, 10.0, -40.0, 40.0, -30.0, 30.0);

	} // resizeGL()


void SolidCubeWidget::cube(){

  // Here are the normals, correctly calculated for the cube faces below  
   GLfloat normals[][3] = { {1., 0. ,0.}, {-1., 0., 0.}, {0., 0., 1.}, {0., 0., -1.} };

  // Here we give every face the same normal
//  GLfloat normals[][3] = { {0.333, 0.333, 0.333 }, {0.333, 0.333, 0.333}, {0.333, 0.333, 0.333}, {0.3333, 0.3333, 0.333}};

  // Here we have permuted the first normal array
  // GLfloat normals[][3] = {  {-1., 0., 0.}, {0., 0., 1.}, {1., 0. ,0.}, {0., 0., -1.} };

  materialStruct* p_front = &brassMaterials;
	
  glMaterialfv(GL_FRONT, GL_AMBIENT,    p_front->ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE,    p_front->diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR,   p_front->specular);
  glMaterialf(GL_FRONT, GL_SHININESS,   p_front->shininess);

  glNormal3fv(normals[0]);
  glBegin(GL_POLYGON);
  glVertex3f(-1.0, -1.0, 1.0);
      glVertex3f(1.0, -1.0, 1.0);
      glVertex3f(1.0, -1.0, -1.0);
      glVertex3f(-1.0, -1.0, -1.0);

glEnd();

}
	
// called every time the widget needs painting
void SolidCubeWidget::paintGL()
	{ // paintGL()
	// clear the widget
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// You must set the matrix mode to model view directly before enabling the depth test

	glEnable(GL_DEPTH_TEST); // comment out depth test to observe the result                                                                                                    


	glPushMatrix();
	glLoadIdentity();
        GLfloat light_pos[] = {0., 0., 10., 1.};
        glDisable(GL_LIGHTING); // remove later.
        glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
        glLightf (GL_LIGHT0, GL_SPOT_CUTOFF,15.);
	glPopMatrix();


	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


//    glRotated(180.,0.,1.,0.);



//    glRotated(90,1,0,0);
//    glRotated(90,0,0,1);

//    glRotated(0,0,0,1);

//    glScaled(0.3,0.3,2);
    std::cout << "sdsd" << std::endl;

    gluLookAt(1.,1.,1., 0.0,0.0,0.0, 0.0,10.0,0.0);
//    glRotatef(90, 0, 1, 0);
    glScalef(6,3,8);
//    glRotatef(90,0,1,0);
    this->cube();

	// flush to screen
	glFlush();	

	} // paintGL()
