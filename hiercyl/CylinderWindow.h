#ifndef __GL_POLYGON_WINDOW_H__
#define __GL_POLYGON_WINDOW_H__ 1

#include <QGLWidget>
#include <QMenuBar>
#include <QSlider>
#include <QTimer>
#include <QBoxLayout>
#include "CylinderWidget.h"

class CylinderWindow: public QWidget
	{ 
	public:
       
	
	// constructor / destructor
	CylinderWindow(QWidget *parent);
	~CylinderWindow();

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
	CylinderWidget *cubeWidget;
	// and a slider for the number of vertices
	QSlider *nSlider;

	QTimer   *pTimer;
	  
	// resets all the interface elements
	void ResetInterface();
	}; 
	
#endif
