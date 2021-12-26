#include <GL/glu.h>
#include <QGLWidget>
#include <cmath>
#include <iostream>

#include "CylinderWidget.h"

// Play with these parameters
static const int N        = 80; // This determines the number of faces of the cylinder
static const int n_div   =  80;  // This determines the fineness of the cylinder along its length


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

static materialStruct uglyMaterials = {
  { 1.0 , 0.0, 0.0, 1.0},
  { 0. ,  0.0,  0.0, 1.0},
  { 0.0, 0.0,  1.0, 1.0},
  100.0 
};

static materialStruct greenRubber = {
				     { 0.0f,0.05f,0.0f,1.0f },
				     { 0.4f,0.5f,0.4f,1.0f},
				     {0.04f,0.7f,0.04f,1.0f },
				     10.0f };

static materialStruct emeraldMaterial = {
					 { 0.1f, 0.18725f, 0.1745f, 0.8f },
					 {0.396f, 0.74151f, 0.69102f, 0.8f },
					 {0.297254f, 0.30829f, 0.306678f, 0.8f },
					 12.8f };


static materialStruct yellowPlastic = {
				       {0.0f,0.0f,0.0f,1.0f },
				       {0.5f,0.5f,0.0f,1.0f },
				       {0.60f,0.60f,0.50f,1.0f },
				       32.0f};

static materialStruct ruby = {
			      { 0.1745f, 0.01175f, 0.01175f, 0.55f },
			      {0.61424f, 0.04136f, 0.04136f, 0.55f },
			      {0.727811f, 0.626959f, 0.626959f, 0.55f },
			      76.8f};

static const float PI = 3.1415926535;

// constructor
CylinderWidget::CylinderWidget(QWidget *parent)
  : QGLWidget(parent),
    _angle(0),
    _time(0),
  slider_1_angle(0),
  slider_2(0),
  slider_3(1),
  slider_4(0)
	{ // constructor       

	} // constructor

// called when OpenGL context is set up
void CylinderWidget::initializeGL()
	{ // initializeGL()
	// set the widget background colour
	glClearColor(0.3, 0.3, 0.3, 0.0);
	glOrtho(-4.,4.,-4.,4.,-4.,4);
 
	} // initializeGL()

void CylinderWidget::updateAngle(int i){
  _angle = i;
  this->repaint();
}

void CylinderWidget::updateAngle(){
  _time += 10.0;
  this->repaint();
}
  
// called every time the widget is resized
void CylinderWidget::resizeGL(int w, int h)
	{ // resizeGL()
	// set the viewport to the entire widget
	glViewport(0, 0, w, h);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	GLfloat light_pos[] = {2., -2.,-2., 1.};

	glEnable(GL_LIGHTING); // enable lighting in general
        glEnable(GL_LIGHT0);   // each light source must also be enabled


	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);

        
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    glOrtho(-20.0, 20.0, -20.0, 20.0, -450.0, 450.0); // quick fix is to increase far.

	} // resizeGL()

void CylinderWidget::normalize(GLfloat* vector)
{
  GLfloat norm = sqrt(vector[0]*vector[0] + vector[1]*vector[1] + vector[2]*vector[2]);
  vector[0] /= norm;
  vector[1] /= norm;
  vector[2] /= norm; 
}



void CylinderWidget::rotateAround(int i){
    slider_1_angle = i;
    this->repaint();
}

void CylinderWidget::moveUpDown(int i){
    slider_2 = i;
    this->repaint();
}

void CylinderWidget::zoomIn(int i){
    slider_3 = i;
    this->repaint();
}

void CylinderWidget::panLeftRight(int i){
    slider_4 = i;
    this->repaint();
}

void CylinderWidget::flatplane(const materialStruct* p_front){
    glMaterialfv(GL_FRONT, GL_AMBIENT,    p_front->ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,    p_front->diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,   p_front->specular);
    glMaterialf(GL_FRONT, GL_SHININESS,   p_front->shininess);
//    glRotatef(180, 0, 1, 0);
//        glTranslatef(90, 0, 0); //Moves it down,


    glBegin(GL_POLYGON);
    glVertex3f(-1.0, -1.0, 0.0);
    glVertex3f(1.0, -1.0, 0.0);
    glVertex3f(1.0, 1.0, 0.0);
    glVertex3f(-1.0, 1.0, 0.0);
    glEnd();

}


void CylinderWidget::tree(){ // so the idea is to scale the stuff here and move in paintGL. I think xd.

    glPushMatrix();
    glScalef(4,4,10); // deform cylinder
    this->cylinder(&greenRubber);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0,0,15); // first moves forwards back, middle moves sideway, last up n down
    glScalef(4.5,4.5,4.5); // deform cylinder
    glRotatef(90,1,0,0);
    this->pyramid(&greenRubber);
    glPopMatrix();

}

void CylinderWidget::pyramid(const materialStruct* p_front){

glMaterialfv(GL_FRONT, GL_AMBIENT,    p_front->ambient);
glMaterialfv(GL_FRONT, GL_DIFFUSE,    p_front->diffuse);
glMaterialfv(GL_FRONT, GL_SPECULAR,   p_front->specular);
glMaterialf(GL_FRONT, GL_SHININESS,   p_front->shininess);

glBegin(GL_TRIANGLES);
  //Triangle 1
    glColor3f(1.0f,0.0f,0.0f); glVertex3f( 0.0f, 1.0f, 0.0f);   //V0(red)
    glColor3f(0.0f,1.0f,0.0f); glVertex3f(-1.0f,-1.0f, 1.0f);   //V1(green)
    glColor3f(0.0f,0.0f,1.0f); glVertex3f( 1.0f,-1.0f, 1.0f);   //V2(blue)
  //Triangle 2
    glColor3f(1.0f,0.0f,0.0f); glVertex3f( 0.0f, 1.0f, 0.0f);   //V0(red)
    glColor3f(0.0f,0.0f,1.0f); glVertex3f( 1.0f,-1.0f, 1.0f);   //V2(blue)
    glColor3f(0.0f,1.0f,0.0f); glVertex3f( 1.0f,-1.0f,-1.0f);   //V3(green)
  //Triangle 3
    glColor3f(1.0f,0.0f,0.0f); glVertex3f( 0.0f, 1.0f, 0.0f);   //V0(red)
    glColor3f(0.0f,1.0f,0.0f); glVertex3f( 1.0f,-1.0f,-1.0f);   //V3(green)
    glColor3f(0.0f,0.0f,1.0f); glVertex3f(-1.0f,-1.0f,-1.0f);   //V4(blue)
  //Triangle 4
    glColor3f(1.0f,0.0f,0.0f); glVertex3f( 0.0f, 1.0f, 0.0f);   //V0(red)
    glColor3f(0.0f,0.0f,1.0f); glVertex3f(-1.0f,-1.0f,-1.0f);   //V4(blue)
    glColor3f(0.0f,1.0f,0.0f); glVertex3f(-1.0f,-1.0f, 1.0f);   //V1(green)
glEnd();
}

void CylinderWidget::sphere(const materialStruct* p_front ){
	
   glMaterialfv(GL_FRONT, GL_AMBIENT,    p_front->ambient);
   glMaterialfv(GL_FRONT, GL_DIFFUSE,    p_front->diffuse);
   glMaterialfv(GL_FRONT, GL_SPECULAR,   p_front->specular);
   glMaterialf(GL_FRONT, GL_SHININESS,   p_front->shininess);

  constexpr double pi = 3.14159265358979323846;
  float phi_min = 0;
  float phi_max = 2*pi;

  float theta_min = -pi;
  float theta_max = pi;

  int n_theta = 50;
  int n_phi   = 50;

  float delta_phi   = (phi_max - phi_min)/n_phi;
  float delta_theta = (theta_max - theta_min)/n_theta;

  for (int i_phi = 0; i_phi < n_phi; i_phi++)
    for (int i_theta = 0; i_theta < n_theta; i_theta++){

      glBegin(GL_POLYGON);
      float phi   = phi_min + i_phi*delta_phi;
      float theta = theta_min + i_theta*delta_theta;

      float x_0 = cos(phi)*sin(theta);
      float y_0 = sin(phi)*sin(theta);
      float z_0 = cos(theta);
      glNormal3f(x_0,y_0,z_0);
      glVertex3f(x_0,y_0,z_0);
      float x_1 = cos(phi+delta_phi)*sin(theta);
      float y_1 = sin(phi+delta_phi)*sin(theta);
      float z_1 = cos(theta);
      glNormal3f(x_1,y_1,z_1);
      glVertex3f(x_1,y_1,z_1);
      float x_2 = cos(phi+delta_phi)*sin(theta+delta_theta);
      float y_2 = sin(phi+delta_phi)*sin(theta+delta_phi);
      float z_2 = cos(theta + delta_theta);
      glNormal3f(x_2,y_2,z_2);
      glVertex3f(x_2,y_2,z_2);
      float x_3 = cos(phi)*sin(theta);
      float y_3 = sin(phi)*sin(theta);
      float z_3 = cos(theta + delta_theta);
      glNormal3f(x_3,y_3,z_3);
      glVertex3f(x_3,y_3,z_3);

      
      glEnd();
      
    }
}

void CylinderWidget::cylinder(const materialStruct* p_front){


	
   glMaterialfv(GL_FRONT, GL_AMBIENT,    p_front->ambient);
   glMaterialfv(GL_FRONT, GL_DIFFUSE,    p_front->diffuse);
   glMaterialfv(GL_FRONT, GL_SPECULAR,   p_front->specular);
   glMaterialf(GL_FRONT, GL_SHININESS,   p_front->shininess);
	
  
  float x0, x1, y0, y1;

  float z_min = -1;
  float z_max =  1;

  float delta_z = (z_max - z_min)/n_div;
  
  for (int i = 0; i < N; i++){
    for(int i_z = 0; i_z < n_div; i_z++){
      x0 = cos(2*i*PI/N);
      x1 = cos(2*(i+1)*PI/N);
      y0 = sin(2*i*PI/N);
      y1 = sin(2*(i+1)*PI/N);

      float z = z_min + i_z*delta_z;
      glBegin(GL_POLYGON);
      glVertex3f(x0,y0,z);
      glNormal3f(x0,y0,0);
      glVertex3f(x1,y1,z);
      glNormal3f(x1,y1,0);
      glVertex3f(x1,y1,z+delta_z);
      glNormal3f(x1,y1,0);
      glVertex3f(x0,y0,z+delta_z);
      glNormal3f(x0,y0,0);
      glEnd();
    }
  }
}

void CylinderWidget::arm(double upper, double lower, double time){
  double angle = upper*sin(0.1*time) + upper;
  glPushMatrix();
  glRotatef(angle,0.,1.,0.);
  glScalef(0.3,0.3,2.); // deform cylinder
  glTranslatef(0.,0.,-1);
  this->cylinder(&greenRubber);
  glTranslatef(0.,0.,-1);
  glScalef(0.6/0.3,0.6/0.3,0.6/2.);
  this->sphere(&yellowPlastic);
  glScalef(1/0.6,1/0.6,1/0.6); // here we have undone all scalings; the origin is at the end of the upper arm  and the z-axis is aligned with that arm

  glPushMatrix();
  double lowangle = lower*sin(0.2*time) + lower;
  glRotatef(lowangle,0.,1.,0.);
  glScalef(0.3,0.3,2.); // deform cylinder
  glTranslatef(0.,0.,-1);
  this->cylinder(&greenRubber);
  glTranslatef(0.,0.,-1);
  glScalef(0.6/0.3,0.6/0.3,0.6/2.);
  this->sphere(&yellowPlastic);
  glPopMatrix();
  glPopMatrix();
  glPushMatrix();
  glScalef(0.7,0.7,0.7);
  this->sphere(&yellowPlastic);
  glPopMatrix();
     
}

void CylinderWidget::body(double time){

  double z_min = -1; // the min and max coordinates in z of the cylinder
  double z_max =  1; // could have made them class constants, or created a robot class

  this->sphere(&emeraldMaterial);
  glPushMatrix();
  glTranslatef(0.,0.,-1);
  glScalef(0.5,0.5,1.0);
  this->cylinder(&greenRubber);
  glPopMatrix(); // revert back to the original coordinate system
  glTranslatef(0.,0.,z_min-z_max);
  glPushMatrix(); // keep the end position of the 'neck'
  glScalef(0.6,0.6,0.6);
  this->sphere(&yellowPlastic);
  glPopMatrix(); // undo scaling and
  glPushMatrix(); // keep the end position of the neck
  glRotatef(90,1.,0.,0.);
  double shoulder_width = 3.0;
  glScalef(0.4,0.4,shoulder_width);
  this->cylinder(&ruby);
  glPopMatrix();
  glPushMatrix();
  glTranslatef(0,-shoulder_width,0);
  arm(45.,20,time);
  glPopMatrix();
  glPushMatrix();
  glTranslatef(0, shoulder_width,0);
  arm(30.,70.,time);
  glPopMatrix();
  glPushMatrix();
  glTranslatef(0.,0.,-2.5);
  glScalef(1,1,3);
  this->cylinder(&ruby);
  glPopMatrix();
}

// called every time the widget needs painting
void CylinderWidget::paintGL()
    { // paintGL()
	// clear the widget
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_NORMALIZE);
        glShadeModel(GL_FLAT);
//        glDisable(GL_LIGHTING);

	// You must set the matrix mode to model view directly before enabling the depth test
      	glMatrixMode(GL_MODELVIEW);
       	glEnable(GL_DEPTH_TEST); //

	
    glLoadIdentity();

    gluLookAt(2.3,1.,1., 0.0,0.0,0.0, 0.0,0.0,1.0);

    if(slider_3 == 0){
        slider_3 = 1;
    }

    glScalef(static_cast<float>(slider_3),static_cast<float>(slider_3),static_cast<float>(slider_3));
    std::cout << slider_4 << std::endl;


    glPushMatrix();
    glRotatef(slider_1_angle,0.,0.,1.);
    glTranslatef(0.,0.,slider_2);
    glTranslatef(0,(slider_4 * -1),0);


//        glRotatef(180, 0, 1, 0);
        glPushMatrix();

        glScalef(12,12,12); //scale the floor - scale first
        glPushMatrix();
        flatplane(&ruby); //draw floor


        glPopMatrix(); // pop
        glPopMatrix(); // pop

        //back to the original matrix.

        glPushMatrix();


//        glTranslatef(0.,-10.,0.);

//        glScalef(5,8,0);

        glTranslatef(0,0,5);
        glScalef(0.3,0.3,0.3);

        body(_time);
        glPopMatrix(); // pop

        glPushMatrix();
        glScalef(0.3,0.3,0.3);
        glTranslatef(2,25.,5); // x is forward and back,y is side ways, z is up or down.
        tree(); //tree 1
        glPopMatrix(); // pop




        glPopMatrix(); // KEEP THIS AT THE END







	// flush to screen
	glFlush();	

	} // paintGL()
