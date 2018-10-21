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
	QLabel* m_pIconLabel;               // 标题栏图标;
	QLabel* m_pTitleLabel;				// 标题栏内容;
	PictureViewToolButton* m_pMenuButton;
	PictureViewToolButton* m_pMinimizeButton;    // 最小化按钮;
	PictureViewToolButton* m_pMaximizeButton;    // 最大化按钮;
	PictureViewToolButton* m_pCloseButton;       // 关闭按钮;
	QPoint m_restorePos;				// 最大化，最小化变量;
	BOOL m_bPressed;					// 移动窗口的变量;
	QPoint m_startMovePos;
	QTimer m_titleRollTimer;			// 标题栏跑马灯效果时钟;
	QString m_titleContent;				// 标题栏内容;

	PictureViewPopMenu* m_pMenu;
	PictureViewMenuItem* m_pOpenfileItem;			//打开图片
	PictureViewMenuItem* m_pSaveFileItem;			//另存图片
	PictureViewMenuItem* m_pPrintPictureItem;		//打印图片
	PictureViewMenuItem* m_pClipperItem;			//图片裁剪
	PictureViewMenuItem* m_pScreenshotItem;			//截图
	PictureViewMenuItem* m_pFilterItem;				//图像滤波
	PictureViewMenuItem* m_pFaceRecognition;		//人脸识别
	PictureViewMenuItem* m_pCameraItem;				//拍照
	PictureViewMenuItem* m_pCloseFileItem;			//关闭图片
};
