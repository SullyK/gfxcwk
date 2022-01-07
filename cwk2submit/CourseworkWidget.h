#ifndef __GL_POLYGON_WIDGET_H__
#define __GL_POLYGON_WIDGET_H__ 1

#include <QGLWidget>
#include <QImage>
#include "Image.h"



struct materialStruct;

class CourseworkWidget: public QGLWidget
	{ // 

	Q_OBJECT

	public:
    CourseworkWidget(QWidget *parent);

	public slots:
    // public slot functions which are called when the slider is moved
	void updateAngle(int);
	void updateAngle();
    void rotateAround(int);
    void moveUpDown(int);
    void zoomIn(int);
    void panLeftRight(int);
    void speedStop();
    void speedOne();
    void speedTwo();
    void speedThree();
    void disableLighting();

	  
	protected:
	// called when OpenGL context is set up
	void initializeGL();
	// called every time the widget is resized
	void resizeGL(int w, int h);
	// called every time the widget needs painting
	void paintGL();

	private:

      //functions used in the project
	  void cylinder(const materialStruct*);
	  void sphere(const materialStruct*);
	  void body(double);
	  void arm(double, double, double);
      void floor(const materialStruct*);
      void treeBasic();
      void treeBranches();
      void pyramid(const materialStruct*);
	  void normalize(GLfloat*);  
      void windTrunk(const materialStruct*);
      void windBlade(const materialStruct*);
      void windHead(const materialStruct*);
      void windMill(double);
      void tankCannon(const materialStruct*);
      void tankHead(const materialStruct*);
      void tankHeadCover(const materialStruct*);
      void tankMiddleSide(const materialStruct*);
      void tankWheels(const materialStruct*);
      void cube(const materialStruct*);
      void turret();
      void base();
      void tank(double);

      void barn();
      void board(const materialStruct*);
      void globe();


    //instance variables
	double _angle;
	double _time;
    double slider_1_angle;
    double slider_2;
    double slider_3;
    double slider_4;
    double position;
    int flag = 1;
    bool lighting = 0;
    Image _image_farm;
    Image _image_poster;
    Image _image_earth;
    QImage* p_qimage;


	  
    }; // class CourseworkWidget
	
#endif
