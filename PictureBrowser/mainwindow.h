#pragma once
#include "stdafx.h"
#include "titlebar.h"

class BaseWindow : public QWidget
{
	Q_OBJECT

public:
	BaseWindow(QWidget *parent = 0);
	~BaseWindow();

protected:
	/*void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
	void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
	void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;*/
	void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

protected:
	TitleBar* m_pTitleBar;
};
