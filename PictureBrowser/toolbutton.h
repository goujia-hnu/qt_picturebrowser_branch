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
	void enterEvent(QEvent *) Q_DECL_OVERRIDE;					//�����¼�
	void leaveEvent(QEvent *) Q_DECL_OVERRIDE;					//�뿪�¼�
	void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;	//��갴���¼�
	void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE; //����ͷ��¼� 
private:
	bool m_bPressed;
};
