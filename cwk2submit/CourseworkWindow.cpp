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
    this->nSlider_3->setMaximum(4);
    this->nSlider_3->setValue(1);


    //create slider 4
    nSlider_4 = new QSlider(Qt::Horizontal);
    this->nSlider_4->setMinimum(-20);
    this->nSlider_4->setMaximum(20);


    //set the buttons
    button_0 = new QPushButton("STOP");
    button_1 = new QPushButton("slow");
    button_2 = new QPushButton("medium");
    button_3 = new QPushButton("fast");

    //checkbox
    checkbox = new QCheckBox("Disable Diffusive lighting");

    //signals/slots for checkbox and buttons
    connect(checkbox, SIGNAL(clicked()), cubeWidget, SLOT(disableLighting()));

    connect(button_0, SIGNAL(clicked()), cubeWidget, SLOT(speedStop()));
    connect(button_1, SIGNAL(clicked()), cubeWidget, SLOT(speedOne()));
    connect(button_2, SIGNAL(clicked()), cubeWidget, SLOT(speedTwo()));
    connect(button_3, SIGNAL(clicked()), cubeWidget, SLOT(speedThree()));

    pTimer = new QTimer;
    pTimer->start(1);

    connect(pTimer, SIGNAL(timeout()),  cubeWidget, SLOT(updateAngle()));

    //connect the sliders to slots.
    connect(nSlider, SIGNAL(valueChanged(int)), cubeWidget, SLOT(rotateAround(int)));

    connect(nSlider_2, SIGNAL(valueChanged(int)), cubeWidget, SLOT(moveUpDown(int)));

    connect(nSlider_3, SIGNAL(valueChanged(int)), cubeWidget, SLOT(zoomIn(int)));

    connect(nSlider_4, SIGNAL(valueChanged(int)), cubeWidget, SLOT(panLeftRight(int)));


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
    tank_speed = new QLabel("Control Tank speed");
    tank_speed->setMaximumHeight(13);
    windowLayout->addWidget(tank_speed);


    //create layout and place buttons in them.
    QHBoxLayout* boxlayout = new QHBoxLayout();
    button_0->setMaximumWidth(70);
    boxlayout->addWidget(button_0);
    button_1->setMaximumWidth(70);
    boxlayout->addWidget(button_1);
    button_2->setMaximumWidth(70);
    boxlayout->addWidget(button_2);
    button_3->setMaximumWidth(70);
    boxlayout->addWidget(button_3);

    QWidget *qwid = new QWidget();

    qwid->setLayout(boxlayout); //layout signle grid for the buttons added to qwidget

    qwid->setMaximumHeight(40);

    windowLayout->addWidget(qwid); //add widget to windowlayout


    windowLayout->addWidget(checkbox);


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
    nSlider->setMinimum(0); //reset values
    nSlider->setMaximum(360);
    nSlider->setValue(0);

    nSlider_2->setMinimum(-5);
    nSlider_2->setMaximum(5);
    nSlider_2->setValue(0);
	
    nSlider_3->setMinimum(1);
    nSlider_3->setMaximum(4);
    nSlider_3->setValue(1);


    nSlider_4->setMinimum(-20);
    nSlider_4->setMaximum(20);
    nSlider_4->setValue(0);


	// now force refresh
	cubeWidget->update();
	update();
	} // ResetInterface()
