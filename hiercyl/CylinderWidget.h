#ifndef __GL_POLYGON_WIDGET_H__
#define __GL_POLYGON_WIDGET_H__ 1

#include <QGLWidget>
#include <QImage>
#include "Image.h"



struct materialStruct;

class CylinderWidget: public QGLWidget
	{ // 

	Q_OBJECT

	public:
	CylinderWidget(QWidget *parent);

	public slots:
        // called by the slider in the main window
	void updateAngle(int);
	void updateAngle();
    void rotateAround(int);
    void moveUpDown(int);
    void zoomIn(int);
    void panLeftRight(int);


	  
	protected:
	// called when OpenGL context is set up
	void initializeGL();
	// called every time the widget is resized
	void resizeGL(int w, int h);
	// called every time the widget needs painting
	void paintGL();

	private:

	  void cylinder(const materialStruct*);
	  void sphere(const materialStruct*);
	  void body(double);
	  void arm(double, double, double);
      void flatplane(const materialStruct*);
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
      void tankMiddle(const materialStruct*);
      void tankMiddleSide(const materialStruct*);
      void tankWheels(const materialStruct*);
      void turret();
      void base();
      void tank(double,double);



	double _angle;
	double _time;
    double slider_1_angle;
    double slider_2;
    double slider_3;
    double slider_4;
    Image   _image;
    QImage* p_qimage;


	  
	}; // class CylinderWidget
	
#endif
