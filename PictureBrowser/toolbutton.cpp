#include "stdafx.h"
#include "toolbutton.h"

ToolButton::ToolButton(QWidget *parent) :QPushButton(parent)
{
	m_bPressed = false;
}

ToolButton::~ToolButton()
{

}

void ToolButton::enterEvent(QEvent *)
{
	QPalette pale = this->palette();
	pale.setColor(QPalette::Button, (objectName() == "closeButton") ? Qt::red : ToolButton_HoverColor);
	setPalette(pale);
	setAutoFillBackground(true);
	update();
}

void ToolButton::leaveEvent(QEvent *)
{
	QPalette pale = this->palette();
	pale.setColor(QPalette::Button, TitleBar_BackGround);
	setPalette(pale);
	setAutoFillBackground(true);
	update();
}


void ToolButton::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		m_bPressed = true;
		QPalette pale = this->palette();
		pale.setColor(QPalette::Button, (objectName() == "closeButton") ? Qt::red : ToolButton_PressedColor);
		setPalette(pale);
		setAutoFillBackground(true);
		update();
	}
}

void ToolButton::mouseReleaseEvent(QMouseEvent *event)
{

	if (m_bPressed && this->rect().contains(event->pos()))
	{
		m_bPressed = false;
		update();
		emit clicked();
	}
}

bool ToolButton::event(QEvent *e)
{
	return QPushButton::event(e);
}

void ToolButton::paintEvent(QPaintEvent *paintevent)
{
	QPushButton::paintEvent(paintevent);
}