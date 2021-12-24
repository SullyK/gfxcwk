#include "CylinderWindow.h"

// constructor / destructor
CylinderWindow::CylinderWindow(QWidget *parent)
	: QWidget(parent)
	{ // constructor

	// create menu bar
	menuBar = new QMenuBar(this);
	
	// create file menu
	fileMenu = menuBar->addMenu("&File");

	// create the action
	actionQuit = new QAction("&Quit", this);

	// leave signals & slots to the controller
	
	// add the item to the menu
	fileMenu->addAction(actionQuit);
	
	// create the window layout
	windowLayout = new QBoxLayout(QBoxLayout::TopToBottom, this);

	// create main widget
	cubeWidget = new CylinderWidget(this);
	windowLayout->addWidget(cubeWidget);

	// create slider
	nSlider = new QSlider(Qt::Horizontal);
    this->nSlider->setMinimum(0);
    this->nSlider->setMaximum(360);



    pTimer = new QTimer;
        pTimer->start(10);

        connect(pTimer, SIGNAL(timeout()),  cubeWidget, SLOT(updateAngle()));

    //connect the first slider to slot.
    connect(nSlider, SIGNAL(valueChanged(int)), cubeWidget, SLOT(rotateAround(int)));

	windowLayout->addWidget(nSlider);
	} // constructor

CylinderWindow::~CylinderWindow()
	{ // destructor
	delete nSlider;
	delete cubeWidget;
	delete windowLayout;
	delete actionQuit;
	delete fileMenu;
	delete menuBar;
	} // destructor

// resets all the interface elements
void CylinderWindow::ResetInterface()
	{ // ResetInterface()
	nSlider->setMinimum(0);
    nSlider->setMaximum(360);
	nSlider->setValue(0);
	
	// now force refresh
	cubeWidget->update();
	update();
	} // ResetInterface()
