#ifndef __GL_POLYGON_WIDGET_H__
#define __GL_POLYGON_WIDGET_H__ 1

#include <QGLWidget>

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
      void tree();
      void pyramid(const materialStruct*);
	  void normalize(GLfloat*);  
	  
	double _angle;
	double _time;
    double slider_1_angle;

	  
	}; // class CylinderWidget
	
#endif
