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

    // create slider2
    nSlider_2 = new QSlider(Qt::Horizontal);
    this->nSlider_2->setMinimum(-5);
    this->nSlider_2->setMaximum(5);
    this->nSlider_2->setValue(0);

    //create slider 3
    nSlider_3 = new QSlider(Qt::Horizontal);
    this->nSlider_3->setMinimum(1);
    this->nSlider_3->setMaximum(2);
    this->nSlider_3->setValue(1);


    //pan left and right.
    nSlider_4 = new QSlider(Qt::Horizontal);
    this->nSlider_4->setMinimum(-20);
    this->nSlider_4->setMaximum(20);
    this->nSlider_4->setValue(0); // Qt doesn't like me doing * -1 here. I will do it in the function using slider_4



    pTimer = new QTimer;
    pTimer->start(10);

    connect(pTimer, SIGNAL(timeout()),  cubeWidget, SLOT(updateAngle()));

    //connect the first slider to slot.
    connect(nSlider, SIGNAL(valueChanged(int)), cubeWidget, SLOT(rotateAround(int)));

    connect(nSlider_2, SIGNAL(valueChanged(int)), cubeWidget, SLOT(moveUpDown(int)));

    connect(nSlider_3, SIGNAL(valueChanged(int)), cubeWidget, SLOT(zoomIn(int)));

    connect(nSlider_4, SIGNAL(valueChanged(int)), cubeWidget, SLOT(panLeftRight(int)));

	windowLayout->addWidget(nSlider);
    windowLayout->addWidget(nSlider_2);
    windowLayout->addWidget(nSlider_3);
    windowLayout->addWidget(nSlider_4);


	} // constructor

CylinderWindow::~CylinderWindow()
	{ // destructor
	delete nSlider;
    delete nSlider_2; // 2nd slider
    delete nSlider_3;
    delete nSlider_4;
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

    nSlider_2->setMinimum(-5);
    nSlider_2->setMaximum(5);
    nSlider_2->setValue(0);
	
    nSlider_3->setMinimum(1);
    nSlider_3->setMaximum(2);
    nSlider_3->setValue(1);

    nSlider_4->setMinimum(-20);
    nSlider_4->setMaximum(20);
    nSlider_4->setValue(0);


	// now force refresh
	cubeWidget->update();
	update();
	} // ResetInterface()
