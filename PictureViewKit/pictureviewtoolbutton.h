#pragma once
#include "stdafx.h"
#include "pictureviewkit_global.h"

class PICTUREVIEWKIT_EXPORT PictureViewToolButton :public QPushButton
{
	Q_OBJECT

public:
	PictureViewToolButton(QWidget *parent = Q_NULLPTR);
	~PictureViewToolButton();
	bool isPressed() const;
	bool isHovered() const;
	void setPressed(bool bPressed);

protected:
	void paintEvent(QPaintEvent *) Q_DECL_OVERRIDE;
	//void enterEvent(QEvent *) Q_DECL_OVERRIDE;
	//void leaveEvent(QEvent *) Q_DECL_OVERRIDE;
	void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
	void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

private:
	bool m_bPressed;
	bool m_bHovered;
};