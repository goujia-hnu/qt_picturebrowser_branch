#pragma once
#include "qapplication.h"
#include "qwidget.h"

#if defined(qApp)
#undef qApp
#endif
#define qApp (static_cast<Application *>(QCoreApplication::instance()))

class Application :public QApplication
{
	Q_OBJECT
public:
	Application(int &argc, char **argv);
	virtual ~Application();

	void setMainWidget(QWidget* mainWidget);
	QWidget* mainWidget();

private:
	QWidget* m_mainWidget;
};
