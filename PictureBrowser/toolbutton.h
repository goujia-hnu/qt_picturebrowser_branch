#pragma once
#include "stdafx.h"

class ToolButton :public QPushButton
{
	Q_OBJECT
public:
	ToolButton(QWidget *parent = Q_NULLPTR);
	~ToolButton();
protected:
	bool event(QEvent *e) Q_DECL_OVERRIDE;
	void paintEvent(QPaintEvent *) Q_DECL_OVERRIDE;
	void enterEvent(QEvent *) Q_DECL_OVERRIDE;					//进入事件
	void leaveEvent(QEvent *) Q_DECL_OVERRIDE;					//离开事件
	void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;	//鼠标按下事件
	void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE; //鼠标释放事件 
private:
	bool m_bPressed;
};
