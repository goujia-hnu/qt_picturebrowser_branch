#include "stdafx.h"
#include "basewindow.h"
#include "application.h"

int main(int argc, char *argv[])
{
	Application a(argc, argv);
	BaseWindow w;
	a.setMainWidget(&w);
	w.initWindow();

	PictureViewColorMap::instance();
	w.show();
	return a.exec();
}
