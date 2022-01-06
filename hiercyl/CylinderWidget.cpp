#include <GL/glu.h>
#include <QGLWidget>
#include <cmath>
#include <iostream>

#include "CylinderWidget.h"

//some numbers used in cylinder/sphere calculations(from the tutorials)
static const int N        = 80;
static const int n_div   =  80;


//material struct for adding lighting.
typedef struct materialStruct {
  GLfloat ambient[4];
  GLfloat diffuse[4];
  GLfloat specular[4];
  GLfloat shininess;
} materialStruct;


//different colours used in the project.

static materialStruct blackPlastic = {
  { 0.0f, 0.0f, 0.0f, 1.0f},
  {0.01f, 0.01f, 0.01f, 1.0f},
  {0.50f, 0.50f, 0.50f, 1.0f},
   32.0f
};

static materialStruct polished_copper = {
  { 0.2295f, 0.08825f, 0.0275f, 1.0f},
  {0.5508f, 0.2118f, 0.066f, 1.0f},
  { 0.580594f, 0.223257f, 0.0695701f, 1.0f },
   40.0f
};

static materialStruct whitePlastic = {
  {  0.05f,0.05f,0.05f,1.0f},
  {0.5f,0.5f,0.5f,1.0f},
  { 0.7f,0.7f,0.7f,1.0f},
   10.0f
};


static materialStruct silver = {
  { 0.19225f, 0.19225f, 0.19225f, 1.0f},
  { 0.50754f, 0.50754f, 0.50754f, 1.0f},
  { 0.508273f, 0.508273f, 0.508273f, 1.0f},
   51.2f
};



static materialStruct brownBark = {
  {0.2125f, 0.1275f, 0.054f, 1.0f},
  { 0.714f, 0.4284f, 0.18144f, 1.0f},
  { 0.393548f, 0.271906f, 0.166721f, 1.0f},
  1.6f
};


static materialStruct greenRubber = {
				     { 0.0f,0.05f,0.0f,1.0f },
				     { 0.4f,0.5f,0.4f,1.0f},
				     {0.04f,0.7f,0.04f,1.0f },
				     10.0f };


static materialStruct ruby = {
			      { 0.1745f, 0.01175f, 0.01175f, 0.55f },
			      {0.61424f, 0.04136f, 0.04136f, 0.55f },
			      {0.727811f, 0.626959f, 0.626959f, 0.55f },
			      76.8f};

static const float PI = 3.1415926535; //pi approx

CylinderWidget::CylinderWidget(QWidget *parent) // constructor sets up the project
  : QGLWidget(parent),
    _angle(0),
    _time(0),
  slider_1_angle(0),
  slider_2(0),
  slider_3(1),
  slider_4(0),
  slider_5(1),
  position(0),
  _image_farm("grass2.ppm"),
  _image_poster("poster.ppm"),
  _image_earth("earth.ppm")

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

void CylinderWidget::updateAngle(){ // update the position of tank.
  _time += 10.0;
  position  += 10 + slider_5;
  this->repaint();
}
  
void CylinderWidget::updateSpeed(int i){ //
    slider_5 = i;
    this->repaint();
}

// called every time the widget is resized
void CylinderWidget::resizeGL(int w, int h)
	{ // resizeGL()
	// set the viewport to the entire widget
	glViewport(0, 0, w, h);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();        
	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-20.0, 20.0, -20.0, 20.0, -250.0, 250.0);
    // Ortho is used with a big far and near to ensure no clipping(this is extra big to avoid any issue).


	} // resizeGL()


//these are functions which are affected by the sliders.

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

void CylinderWidget::floor(const materialStruct* p_front){
    //floor, light turned off here.
    // made using gluDisk.
    //similar to below, it's light is turned off, texture is on, then placed, texture off and then light back on.



    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);

    glEnable(GL_TEXTURE_2D);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _image_farm.Width(), _image_farm.Height(), 0, GL_RGB, GL_UNSIGNED_BYTE, _image_farm.imageField());
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


    glBegin(GL_POLYGON);
    GLUquadricObj *quadObj = gluNewQuadric();
    gluQuadricTexture(quadObj,GLU_TRUE);

    gluDisk(quadObj,10,10,100,100);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

}


void CylinderWidget::globe(const materialStruct* p_front){
    //this is the globe of the *far* away earth
    // made using gluSphere.
    //far from the current terrain, so it's light is unaffected by my lighting.
    //similar to below, it's light is turned off, texture is on, then placed, texture off and then light back on.

    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);

    glEnable(GL_TEXTURE_2D);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _image_earth.Width(), _image_earth.Height(), 0, GL_RGB, GL_UNSIGNED_BYTE, _image_earth.imageField());
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


    glBegin(GL_POLYGON);
    GLUquadricObj *quadObj = gluNewQuadric();
    gluQuadricTexture(quadObj,GLU_TRUE);

    gluSphere(quadObj,10,100,100);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}

void CylinderWidget::board(const materialStruct* p_front){
    // This is the board where the textures of marcus and mark are places
    //Lighting is first disabled, then textures enabled,
    //placed and once done, textures are disbaled and light is renabled.
    //lighting left off to show this banner all the time(it's supposed to be lit up).

    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);

    glEnable(GL_TEXTURE_2D);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _image_poster.Width(), _image_poster.Height(), 0, GL_RGB, GL_UNSIGNED_BYTE, _image_poster.imageField());
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glBegin(GL_POLYGON);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-1.0, 0.0, -1.0);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(1.0,  0.0 , -1.0);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(1.0, 0.0, 1.0);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(-1.0, 0.0, 1.0);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

}


void CylinderWidget::treeBasic(){ //Creates a basic tree without branches.

    glPushMatrix();
    glScalef(2,7,2); // The tree trunk
    this->cylinder(&brownBark); //coloured brown.
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,10,0); // move up the branch and place the leaves
    glScalef(5,5,5); // in the form of a sphere(scaled properly).
    this->sphere(&greenRubber);
    glPopMatrix();

}


void CylinderWidget::treeBranches(){ //Creates a tree with branches.

    glPushMatrix();
    glScalef(1.5,12,1.5);
    this->cylinder(&brownBark); // tree turn, coloured brown, and scaled.
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,15,0);
    glScalef(5,5,5);
    this->sphere(&greenRubber); //tree leaves, coloured green, translated to place and scaled
    glPopMatrix(); // back to the start.

    glPushMatrix(); // save the start coordinates
    glTranslatef(3.9,5.5,0); //around half way up the bark
    glRotatef(70,0,0,1);
    glScalef(1,4,1);// rotate sideways.
    this->cylinder(&brownBark); //a branch

    glPopMatrix(); // back to the start.
    glPushMatrix(); // save the start coordinates
    glScalef(3,3,3);
    glTranslatef(3.,1.7,0);
    this->sphere(&greenRubber); //leaves on branch
    glPopMatrix(); // back to the start.

    glPushMatrix(); // save the start coordinates
    glTranslatef(-3.9,5.5,0); //around half way up the bark
    glRotatef(78,0,0,1);
    glScalef(1,4,1);// rotate sideways.
    this->cylinder(&brownBark); //another branch
    glPopMatrix(); // back to the start.

    glPushMatrix(); // save the start coordinates
    glScalef(2,2,2);
    glTranslatef(-3.43  ,3.4,0);
    this->sphere(&greenRubber);
    glPopMatrix(); // leaves on the 2nd branch


}

// for now I will leave pyramid out.
void CylinderWidget::pyramid(const materialStruct* p_front){
    // pyramid shape used in a few places.
    // The normals were calculated by me prior to run time using the method on Khronos Group's website, by hand.
    // There are 4 faces to this pryamid without a base(as it wasn't necessary to have a base for my use cases).

GLfloat normals[][3] = { {0., 0.4472135954999579 ,0.8944271909999159},
                         {0.4472135954999579, 0.4472135954999579, 0.},
                         {0., 0.4472135954999579, -0.8944271909999159},
                         {-0.8944271909999159, 0.4472135954999579, 0}};

glMaterialfv(GL_FRONT, GL_AMBIENT,    p_front->ambient);
glMaterialfv(GL_FRONT, GL_DIFFUSE,    p_front->diffuse);
glMaterialfv(GL_FRONT, GL_SPECULAR,   p_front->specular);
glMaterialf(GL_FRONT, GL_SHININESS,   p_front->shininess);

    glBegin(GL_POLYGON);
    glNormal3fv(normals[0]);
    glVertex3f( 0.0f, 1.0f, 0.0f);
    glVertex3f(-1.0f,-1.0f, 1.0f);
    glVertex3f( 1.0f,-1.0f, 1.0f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3fv(normals[1]);
    glVertex3f( 0.0f, 1.0f, 0.0f);
    glVertex3f( 1.0f,-1.0f, 1.0f);
    glVertex3f( 1.0f,-1.0f,-1.0f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3fv(normals[2]);
    glVertex3f( 0.0f, 1.0f, 0.0f);
    glVertex3f( 1.0f,-1.0f,-1.0f);
    glVertex3f(-1.0f,-1.0f,-1.0f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3fv(normals[3]);
    glVertex3f( 0.0f, 1.0f, 0.0f);
    glVertex3f(-1.0f,-1.0f,-1.0f);
    glVertex3f(-1.0f,-1.0f, 1.0f);
    glEnd();
}

void CylinderWidget::sphere(const materialStruct* p_front ){ //sphere from the tutorial, used in one part, otherwise gluSphere is used
	
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
      glNormal3f(x_0,z_0,y_0);
      glVertex3f(x_0,z_0,y_0);
      float x_1 = cos(phi+delta_phi)*sin(theta);
      float y_1 = sin(phi+delta_phi)*sin(theta);
      float z_1 = cos(theta);
      glNormal3f(x_1,z_1,y_1);
      glVertex3f(x_1,z_1,y_1);
      float x_2 = cos(phi+delta_phi)*sin(theta+delta_theta);
      float y_2 = sin(phi+delta_phi)*sin(theta+delta_phi);
      float z_2 = cos(theta + delta_theta);
      glNormal3f(x_2,z_2,y_2);
      glVertex3f(x_2,z_2,y_2);
      float x_3 = cos(phi)*sin(theta);
      float y_3 = sin(phi)*sin(theta);
      float z_3 = cos(theta + delta_theta);
      glNormal3f(x_3,z_3,y_3);
      glVertex3f(x_3,z_3,y_3);

      
      glEnd();
      
    }
}

void CylinderWidget::cylinder(const materialStruct* p_front){ //used in some parts, provided from the tutorial. Other parts use gluCylinder


	
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
      glVertex3f(x0,z,y0);
      glNormal3f(x0,0,y0);
      glVertex3f(x1,z,y1);
      glNormal3f(x1,y1,0);
      glVertex3f(x1,z+delta_z,y1);
      glNormal3f(x1,0,y1);
      glVertex3f(x0,z+delta_z,y0);
      glNormal3f(x0,0,y0);
      glEnd();
    }
  }
}




void CylinderWidget::windHead(const materialStruct* p_front){ //head of the turbine(where blades connect) is made using sphere provided
                                                              // by the code taught in class/tutorial.

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
       glNormal3f(x_0,z_0,y_0);
       glVertex3f(x_0,z_0,y_0);
       float x_1 = cos(phi+delta_phi)*sin(theta);
       float y_1 = sin(phi+delta_phi)*sin(theta);
       float z_1 = cos(theta);
       glNormal3f(x_1,z_1,y_1);
       glVertex3f(x_1,z_1,y_1);
       float x_2 = cos(phi+delta_phi)*sin(theta+delta_theta);
       float y_2 = sin(phi+delta_phi)*sin(theta+delta_phi);
       float z_2 = cos(theta + delta_theta);
       glNormal3f(x_2,z_2,y_2);
       glVertex3f(x_2,z_2,y_2);
       float x_3 = cos(phi)*sin(theta);
       float y_3 = sin(phi)*sin(theta);
       float z_3 = cos(theta + delta_theta);
       glNormal3f(x_3,z_3,y_3);
       glVertex3f(x_3,z_3,y_3);


       glEnd();

     }
}



void CylinderWidget::windBlade(const materialStruct* p_front){ //blade made using glyCylinder

    glMaterialfv(GL_FRONT, GL_AMBIENT,    p_front->ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,    p_front->diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,   p_front->specular);
    glMaterialf(GL_FRONT, GL_SHININESS,   p_front->shininess);

    glBegin(GL_POLYGON);
    GLUquadricObj *quadObj = gluNewQuadric();
    gluCylinder(quadObj, 1.5, 0., 18., 1000, 100);
    glEnd();


}


void CylinderWidget::windTrunk(const materialStruct* p_front){ //using the method provided in the tutorial to generate a cylinder

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
        glVertex3f(x0,z,y0);
        glNormal3f(x0,0,y0);
        glVertex3f(x1,z,y1);
        glNormal3f(x1,y1,0);
        glVertex3f(x1,z+delta_z,y1);
        glNormal3f(x1,0,y1);
        glVertex3f(x0,z+delta_z,y0);
        glNormal3f(x0,0,y0);
        glEnd();
      }
    }
}

void CylinderWidget::windMill(double time){

    glPushMatrix();
    glScalef(0.5,6,0.5); // The trunk of the wind turbine scaled and placed
    this->windTrunk(&whitePlastic);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0,6.8,0); // Head of the windturbine placed with translate
    this->windHead(&whitePlastic);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.2,7,0);
    glScalef(0.4,0.4,0.4);
    glRotatef(0 + time,1,0,0);
    this->windBlade(&silver); //place the 1rd windturbine blade, translated, scaled and rotated using time to animate
    glPopMatrix();            // the motion of a wind turbine

    glPushMatrix();
    glTranslatef(0.2,7,0);
    glScalef(0.4,0.4,0.4);
    glRotatef(-120 + time,1,0,0);
    this->windBlade(&silver); //place the 2nd windturbine blade
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.2,7,0);
    glScalef(0.4,0.4,0.4);
    glRotatef(-240 + time,1,0,0);
    this->windBlade(&silver); //place the 3rd windturbine blade
    glPopMatrix();
}


void CylinderWidget::tankHead(const materialStruct* p_front){ //head for the tank, made using gluCylinder

    glMaterialfv(GL_FRONT, GL_AMBIENT,    p_front->ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,    p_front->diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,   p_front->specular);
    glMaterialf(GL_FRONT, GL_SHININESS,   p_front->shininess);

    glBegin(GL_POLYGON);
    GLUquadricObj *quadObj = gluNewQuadric();
    gluCylinder(quadObj, 10, 10., 10., 100, 100);
    glEnd();

}

void CylinderWidget::tankHeadCover(const materialStruct* p_front){ // cover for tank head, made using gluDisk
    glMaterialfv(GL_FRONT, GL_AMBIENT,    p_front->ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,    p_front->diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,   p_front->specular);
    glMaterialf(GL_FRONT, GL_SHININESS,   p_front->shininess);

    glBegin(GL_POLYGON);
    GLUquadricObj *quadObj = gluNewQuadric();
    gluDisk(quadObj,10,10,100,100);
    glEnd();
}

void CylinderWidget::tankCannon(const materialStruct* p_front){ //cannon for tank, made using gluCylinder

    glMaterialfv(GL_FRONT, GL_AMBIENT,    p_front->ambient); //give the tank lighting
    glMaterialfv(GL_FRONT, GL_DIFFUSE,    p_front->diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,   p_front->specular);
    glMaterialf(GL_FRONT, GL_SHININESS,   p_front->shininess);

    glBegin(GL_POLYGON);
    GLUquadricObj *quadObj = gluNewQuadric();
    gluCylinder(quadObj, 10, 10., 150., 100, 100);
    glEnd();

}

void CylinderWidget::cube(const materialStruct* p_front){ //cube used for a few different objects such as tank.

    GLfloat normals[][3] = { {0., 1. ,0.}, {0., -1., 0.}, {0., 0., 1.}, {0., 0., -1.}, {-1, 0, 0}, {1, 0, 0} };
    //calculated the normals before runtime(by hand and then inputted).

    glMaterialfv(GL_FRONT, GL_AMBIENT,    p_front->ambient); //give the cube lighting
    glMaterialfv(GL_FRONT, GL_DIFFUSE,    p_front->diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,   p_front->specular);
    glMaterialf(GL_FRONT, GL_SHININESS,   p_front->shininess);


    glBegin(GL_POLYGON); // 6 sides of the cube
    glNormal3fv(normals[0]);
    glVertex3f(1.0f, 1.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3fv(normals[1]);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3fv(normals[2]);
    glVertex3f(1.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3fv(normals[3]);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3fv(normals[4]);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3fv(normals[5]);
    glVertex3f(1.0f, 1.0f, -1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glEnd();

}


void CylinderWidget::tankWheels(const materialStruct* p_front){ //wheels of the tank, made using gluCylinder
    glMaterialfv(GL_FRONT, GL_AMBIENT,    p_front->ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,    p_front->diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,   p_front->specular);
    glMaterialf(GL_FRONT, GL_SHININESS,   p_front->shininess);

    glBegin(GL_POLYGON);
    GLUquadricObj *quadObj = gluNewQuadric();
    gluCylinder(quadObj, 4, 4., 2., 1000, 100);
    glEnd();
}


void CylinderWidget::base(){ // base of the tank ( bottom part of the tank hierachy)

    glPushMatrix();
    glScalef(9,3,9);
    this->cube(&silver); //tank middle made from a cube, scaled appropriately.
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,0,-11.5);
    glScalef(9,3.2,3.2);
    glRotatef(-90,1,0,0);
    this->pyramid(&silver);  // back side of the tank.
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0,0,11.5);
    glScalef(9,3.2,3.2);
    glRotatef(90,1,0,0);
    this->pyramid(&silver);  // front side of the tank.
    glPopMatrix();

    glPushMatrix();
    glTranslatef(10,-1,7);
    glScalef(0.7,0.7,0.7);
    glRotatef(-90,0,1,0);
    this->tankWheels(&ruby); // wheels of the tank
    glPopMatrix();

    glPushMatrix();
    glTranslatef(10,-1,0);
    glScalef(0.7,0.7,0.7);
    glRotatef(-90,0,1,0);
    this->tankWheels(&ruby); // wheels of the tank
    glPopMatrix();


    glPushMatrix();
    glTranslatef(10,-1,-7);
    glScalef(0.7,0.7,0.7);
    glRotatef(-90,0,1,0);
    this->tankWheels(&ruby); // wheels of the tank
    glPopMatrix();


    glPushMatrix();
    glTranslatef(-10,-1,-7);
    glScalef(0.7,0.7,0.7);
    glRotatef(90,0,1,0);
    this->tankWheels(&ruby);  // wheels of the tank
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-10,-1,0);
    glScalef(0.7,0.7,0.7);
    glRotatef(90,0,1,0);
    this->tankWheels(&ruby);  // wheels of the tank
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-10,-1,7);
    glScalef(0.7,0.7,0.7);
    glRotatef(90,0,1,0);
    this->tankWheels(&ruby);  // wheels of the tank
    glPopMatrix();

}

void CylinderWidget::turret(){ // This is the turret (top part of the tank hierachy)

    glPushMatrix(); //start with the head of the tank and scale, translate, rotate if required
    glScalef(0.3,0.3,0.3);
    glRotatef(-90,1,0,0);
    this->tankHead(&ruby);
    glPopMatrix();

    glPushMatrix(); // add the cover to the head and scale, translate, rotate if required
    glScalef(0.3,0.3,0.3);
    glRotatef(270,1,0,0);
    glTranslatef(0,0,10); //3rd done
    this->tankHeadCover(&ruby);
    glPopMatrix();

    glPushMatrix(); // add cannon, scale, translate, rotate if required
    glScalef(0.065,0.065,0.065);
    glTranslatef(0,20,0);
    this->tankCannon(&silver);
    glPopMatrix();


}

void CylinderWidget::tank(double time){
    glPushMatrix();
    glRotatef(position,0.,-1,0); //This essentially allows the whole tank, base and
                                 // turret to be rotated together in a circular fashion
    glPushMatrix();              // as it is pushed but not popped so it affects the code below
    glTranslatef(2,2,18);
    glRotatef(60,0.,-1,0);
    glScalef(0.34,0.34,0.34);
    base(); //Base is translated, rotated and scaled into place
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2,3,18);
    glRotatef(time * 0.5,0.,1,0); //Turret moves as a part of the heirachy requirement, independtly of the base
    glScalef(0.5,0.5,0.5);
    turret();

    glPopMatrix();

    glPopMatrix();
}

void CylinderWidget::barn(){ //barn(house) is made from a cube and a pyramid
    glPushMatrix();
    this->cube(&polished_copper);
    glPopMatrix();
    glPushMatrix();
   glTranslatef(0,2,0);
    this->pyramid(&ruby);
    glPopMatrix();


}

// called every time the widget needs painting
void CylinderWidget::paintGL()
{ // paintGL()
    // clear the widget
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_NORMALIZE);
    glShadeModel(GL_FLAT);

    // You must set the matrix mode to model view directly before enabling the depth test
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST); //

    GLfloat light_pos[] = { 40, 5., -10, 1 }; //light is positioned at this location

    glEnable(GL_LIGHTING); // enable lighting in general
    glEnable(GL_LIGHT0); // each light source must also be enabled
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 180); //light positioned and given a sput cutoff of 180 degrees

    GLfloat ambient_light[] = { .6, .6, .6, 1. };
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light); // enable ambient lighting

    GLfloat diffuse_light[] = { 1, 1, 1, 1 };
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light); // enable Diffused lighting

    GLfloat specular_light[] = { 0.5, 0.5, 0.5, 1 };
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light); // enable Specular lighting

    glLoadIdentity();

    gluLookAt(2.3, 0.7, 1., 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    glScalef(slider_3, slider_3, slider_3); // This globally zooms in by scaling the world.
    glRotatef(slider_1_angle, 0., 1., 0.); // This globally rotates the world, to make it look like the camera is being moved.
    glTranslatef(0., slider_2, 0.0); // This moves the camera up and down via translation.
    glTranslatef(0, 0, (slider_4 * -1)); // This pans the camera left and right via translation.

    glPushMatrix(); //windmill 1 (on left), translated to position.
    glTranslatef(-3., 5., 10.);
    windMill(_time);
    glPopMatrix();

    glPushMatrix(); //windmill 2 (on right), translated to position
    glTranslatef(-3., 5., -10.);
    windMill(_time);
    glPopMatrix();

    glPushMatrix();

    glPushMatrix(); //draws the floor, along with scaling and rotating
    glScalef(2.6, 2.6, 2.6);
    glRotatef(270, 1, 0, 0);
    floor(&whitePlastic);
    glPopMatrix();

    //tree 1 - basic tree with scaling, translation and rotation
    glPushMatrix();
    glScalef(0.3, 0.3, 0.3);
    glTranslatef(15, 5, -15.);
    glRotatef(-90, 0, 1, 0);
    treeBasic(); //tree 1
    glPopMatrix(); // pop

    //tree 2 - more advanced tree with scaling, translation and rotation
    glPushMatrix();
    glScalef(0.3, 0.3, 0.3);
    glTranslatef(-15., 5., -25.);
    glRotatef(-90, 0, 1, 0);
    treeBranches(); //tree 2
    glPopMatrix(); // pop

    //both of the trees below are the same as above just placed in the left hand side
    glScalef(0.3, 0.3, 0.3);
    glTranslatef(15, 5, 15.);
    glRotatef(-90, 0, 1, 0);
    treeBasic(); //tree 3
    glPopMatrix();

    glPushMatrix();
    glScalef(0.3, 0.3, 0.3);
    glTranslatef(-15., 5., 25.);
    glRotatef(-90, 0, 1, 0);
    treeBranches(); //tree 4
    glPopMatrix();

    glPushMatrix();
    tank(slider_5); // Tank takes in the time and slider_5(position) for animated movement
    glPopMatrix();

    glPushMatrix(); //barn(in the middle of the land). Translated and scaled
    glTranslatef(0, 2, 0);
    glScalef(3, 3, 3);
    barn();
    glPopMatrix();

    glPushMatrix(); // created the billboard from a poll(cylinder) and board(flat plane)
    glScalef(0.5, 5, 0.5);
    glTranslatef(47, 1, -10);
    this->cylinder(&blackPlastic); //TODO: CHANGE COLOUR OF THIS POLL. MAYBE REFACTOR THIS AREA.
    glPopMatrix();
    glPushMatrix();
    glTranslatef(24, 10, -5);
    glRotatef(-90, 1, 0, 0);
    glRotatef(90, 0, 0, 1);
    glScalef(5, 5, 5);
    board(&ruby);
    glPopMatrix();

    glPushMatrix(); // Sphere with earth texture added on here, which rotates.
    glTranslatef(-50, 0, -20);
    glScalef(0.15, .15, 0.15);
    glRotatef(0.2 * _time, 0, 1, 0);
    glRotatef(0.05 * _time, 0, 0, 1);
    globe(&ruby);
    glPopMatrix();

    glPopMatrix();

    // flush to screen
    glFlush();

} // paintGL()
