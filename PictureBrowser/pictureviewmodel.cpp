#include "stdafx.h"
#include "pictureviewmodel.h"

PictureViewModel::PictureViewModel(QWidget *parent)
	:QWidget(parent)
{
	m_pView = new PictureView(this);
	QVBoxLayout* vlayout = new QVBoxLayout(this);
	vlayout->addStretch();
	vlayout->addWidget(m_pView);
	vlayout->addStretch();
	setLayout(vlayout);
}

PictureViewModel::~PictureViewModel()
{

}

