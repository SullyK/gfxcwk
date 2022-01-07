#include <QApplication>
#include <QVBoxLayout>
#include "CourseworkWindow.h"

int main(int argc, char *argv[])
	{ // main()
	// create the application
	QApplication app(argc, argv);

	// create model (polygon) as a triangle
	//	GLPolygon *polygon = new GLPolygon();

	// create a master widget
        CourseworkWindow *window = new CourseworkWindow(NULL);


	// resize the window
	window->resize(512, 612);

	// show the label
	window->show();

	// start it running
	app.exec();

	// clean up
	//	delete controller;
	delete window;
	
	// return to caller
	return 0; 
	} // main()
