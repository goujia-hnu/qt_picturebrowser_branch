#include "stdafx.h"
#include "application.h"

Application::Application(int &argc, char **argv)
	:QApplication(argc,argv)
{

}

Application::~Application()
{

}

void Application::setMainWidget(QWidget* mainWidget)
{
	m_mainWidget = mainWidget;
}

QWidget* Application::mainWidget()
{
	return m_mainWidget;
}