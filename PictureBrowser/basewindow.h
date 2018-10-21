#pragma once
#include "stdafx.h"
#include "pictureviewtitlebar.h"
#include "pictureviewwidget.h"

class BaseWindow : public QWidget
{
	Q_OBJECT

public:
	enum Direction {
		UP = 0,
		DOWN = 1,
		LEFT,
		RIGHT,
		LEFTTOP,
		LEFTBOTTOM,
		RIGHTBOTTOM,
		RIGHTTOP,
		NONE
	};
	BaseWindow(QWidget *parent = 0);
	~BaseWindow();
	TitleBar* getTitleBar();
	PictureViewWidget* getPictureViewWidget();
	void initWindow();
protected:
	void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
	void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
	void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
	void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
	bool event(QEvent*event) Q_DECL_OVERRIDE;
	void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;

	void calRegion(const QPoint& cursorpoint);

protected:
	TitleBar*			m_pTitleBar;
	PictureViewWidget*	m_pPictureViewWidget;
	bool				m_bLeftPressDown;
	QPoint				m_pressedPoint;
	Direction			m_direction;
	QVBoxLayout*		m_pLayout;
};
