#include "CourseworkWindow.h"

// constructor / destructor
CourseworkWindow::CourseworkWindow(QWidget *parent)
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
    cubeWidget = new CourseworkWidget(this);
	windowLayout->addWidget(cubeWidget);

	// create slider
	nSlider = new QSlider(Qt::Horizontal);
    this->nSlider->setMinimum(0);
    this->nSlider->setMaximum(360);

    // create slider2
    nSlider_2 = new QSlider(Qt::Horizontal);
    this->nSlider_2->setMinimum(-5);
    this->nSlider_2->setMaximum(5);

    //create slider 3
    nSlider_3 = new QSlider(Qt::Horizontal);
    this->nSlider_3->setMinimum(1);
    this->nSlider_3->setMaximum(4); //get this to down to 2.5 with -0.5 in the function that uses it.
    this->nSlider_3->setValue(1);


    //create slider 4
    nSlider_4 = new QSlider(Qt::Horizontal);
    this->nSlider_4->setMinimum(-20);
    this->nSlider_4->setMaximum(20);


    //create slider 5
    nSlider_5 = new QSlider(Qt::Horizontal);
    this->nSlider_5->setMinimum(-10);
    this->nSlider_5->setMaximum(5);
    this->nSlider_5->setValue(-5);

    pTimer = new QTimer;
    pTimer->start(1);

    connect(pTimer, SIGNAL(timeout()),  cubeWidget, SLOT(updateAngle()));

    //connect the sliders to slots.
    connect(nSlider, SIGNAL(valueChanged(int)), cubeWidget, SLOT(rotateAround(int)));

    connect(nSlider_2, SIGNAL(valueChanged(int)), cubeWidget, SLOT(moveUpDown(int)));

    connect(nSlider_3, SIGNAL(valueChanged(int)), cubeWidget, SLOT(zoomIn(int)));

    connect(nSlider_4, SIGNAL(valueChanged(int)), cubeWidget, SLOT(panLeftRight(int)));

    connect(nSlider_5, SIGNAL(valueChanged(int)), cubeWidget, SLOT(updateSpeed(int)));


    //add labels and sliders to windowLayout.
    slider_1 = new QLabel("Rotate camera");
    slider_1->setMaximumHeight(10);
    windowLayout->addWidget(slider_1);
	windowLayout->addWidget(nSlider);
    slider_2 = new QLabel("Move camera up or down");
    slider_2->setMaximumHeight(13);
    windowLayout->addWidget(slider_2);
    windowLayout->addWidget(nSlider_2);
    slider_3 = new QLabel("Zoom in or out");
    slider_3->setMaximumHeight(10);
    windowLayout->addWidget(slider_3);
    windowLayout->addWidget(nSlider_3);
    slider_4 = new QLabel("Pan left or right");
    slider_4->setMaximumHeight(13);
    windowLayout->addWidget(slider_4);
    windowLayout->addWidget(nSlider_4);
    slider_5 = new QLabel("Change speed of the tank");
    slider_5->setMaximumHeight(13);
    windowLayout->addWidget(slider_5);

    windowLayout->addWidget(nSlider_5);





	} // constructor

CourseworkWindow::~CourseworkWindow()
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
void CourseworkWindow::ResetInterface()
	{ // ResetInterface()
    nSlider->setMinimum(0);
    nSlider->setMaximum(360);
    nSlider->setValue(0);

    nSlider_2->setMinimum(-5);
    nSlider_2->setMaximum(5);
    nSlider_2->setValue(0);
	
    nSlider_3->setMinimum(1);
    nSlider_3->setMaximum(4); //get this to down to 2.5 with -0.5 in the function that uses it.
    nSlider_3->setValue(1);


    nSlider_4->setMinimum(-20);
    nSlider_4->setMaximum(20);
    nSlider_4->setValue(0);

    nSlider_5->setMinimum(-10);
    nSlider_5->setMaximum(5);
    nSlider_5->setValue(-5);


	// now force refresh
	cubeWidget->update();
	update();
	} // ResetInterface()
