#pragma once
#include "qwidget.h"
#include "pictureview.h"

class PictureViewModel : public QWidget
{
	Q_OBJECT
public:
	PictureViewModel(QWidget *parent = Q_NULLPTR);
	~PictureViewModel();


private:
	PictureView* m_pView;
};
