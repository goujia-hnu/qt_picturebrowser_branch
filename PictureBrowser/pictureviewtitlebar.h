#pragma once

#include "stdafx.h"
#include "pictureviewtoolbutton.h"
#include "pictureviewpopmenu.h"

class TitleBar : public QWidget
{
	Q_OBJECT
public:
	TitleBar(QWidget *parent);
	~TitleBar();
	void setTitleIcon(QString filePath, QSize IconSize = QSize(30, 30));
	void setPictureName(QString name);
	void setTitleWidth(int width);
	void createPopMenu();
	void initTitlebar();
	void initOpenfileMenu();
	void initClosefileMenu();

protected:
	virtual void paintEvent(QPaintEvent *event);
	virtual void mouseDoubleClickEvent(QMouseEvent *event);
	virtual void mousePressEvent(QMouseEvent *event);
	virtual void mouseReleaseEvent(QMouseEvent *event);
	virtual void mouseMoveEvent(QMouseEvent *event);
	virtual bool eventFilter(QObject *obj, QEvent *event);

	void updateMaximize();

private slots:
	void onClicked();
	void showMenu();

private:
	QLabel* m_pIconLabel;               // ������ͼ��;
	QLabel* m_pTitleLabel;				// ����������;
	PictureViewToolButton* m_pMenuButton;
	PictureViewToolButton* m_pMinimizeButton;    // ��С����ť;
	PictureViewToolButton* m_pMaximizeButton;    // ��󻯰�ť;
	PictureViewToolButton* m_pCloseButton;       // �رհ�ť;
	QPoint m_restorePos;				// ��󻯣���С������;
	BOOL m_bPressed;					// �ƶ����ڵı���;
	QPoint m_startMovePos;
	QTimer m_titleRollTimer;			// �����������Ч��ʱ��;
	QString m_titleContent;				// ����������;

	PictureViewPopMenu* m_pMenu;
	PictureViewMenuItem* m_pOpenfileItem;			//��ͼƬ
	PictureViewMenuItem* m_pSaveFileItem;			//���ͼƬ
	PictureViewMenuItem* m_pPrintPictureItem;		//��ӡͼƬ
	PictureViewMenuItem* m_pClipperItem;			//ͼƬ�ü�
	PictureViewMenuItem* m_pScreenshotItem;			//��ͼ
	PictureViewMenuItem* m_pFilterItem;				//ͼ���˲�
	PictureViewMenuItem* m_pFaceRecognition;		//����ʶ��
	PictureViewMenuItem* m_pCameraItem;				//����
	PictureViewMenuItem* m_pCloseFileItem;			//�ر�ͼƬ
};
