#ifndef __GL_POLYGON_WINDOW_H__
#define __GL_POLYGON_WINDOW_H__ 1

#include <QGLWidget>
#include <QMenuBar>
#include <QSlider>
#include <QTimer>
#include <QBoxLayout>
#include <QLabel>
#include "CourseworkWidget.h"

class CourseworkWindow: public QWidget
	{ 
	public:
       
	
	// constructor / destructor
    CourseworkWindow(QWidget *parent);
    ~CourseworkWindow();

	// visual hierarchy
	// menu bar
	QMenuBar *menuBar;
		// file menu
		QMenu *fileMenu;
			// quit action
			QAction *actionQuit;

	// window layout
	QBoxLayout *windowLayout;

	// beneath that, the main widget
    CourseworkWidget *cubeWidget;

    //Sliders setup
    QSlider *nSlider;
    QSlider *nSlider_2;
    QSlider *nSlider_3;
    QSlider *nSlider_4;
    QSlider *nSlider_5;
    //Timer setup
    QTimer   *pTimer;


    // label setup
    QLabel *slider_1;
    QLabel *slider_2;
    QLabel *slider_3;
    QLabel *slider_4;
    QLabel *slider_5;

	// resets all the interface elements
	void ResetInterface();
	}; 
	
#endif
