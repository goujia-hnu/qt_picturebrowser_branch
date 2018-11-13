#pragma once
#include "application.h"
#include "pictureviewtoolbutton.h"
#include "pictureviewtitlebar.h"

class PictureView :public QWidget
{
	Q_OBJECT
public:
	enum  Type 
	{
		None = 0,
		Amplification,
		Shrink,
		Lift,
		Right,
		Up,
		Down,
		Move
	};
	PictureView(QWidget* parent = Q_NULLPTR);
	~PictureView();
	void setShowLogo(BOOL visible);
	void setTitleBar(TitleBar* titlebar);
	void initPictureView();
	QRect calculateShowRect();
	QString fileSize2Str(double size);
	void updateTitleText();

public slots:
	bool eventFilter(QObject*, QEvent*) override;
	void wheelEvent(QWheelEvent* event) override;
	void onOpenFile();
	void onCloseFile();

protected:
	bool selectFile();
	void paintEvent(QPaintEvent* event) override;
	bool event(QEvent* event) override;
	void resizeEvent(QResizeEvent* event) override;
	void mouseMoveEvent(QMouseEvent *event) override;
	void mousePressEvent(QMouseEvent *event) override;
	void mouseReleaseEvent(QMouseEvent *event) override;

private:
	QLabel*						m_pLogoLabel;       //LOGO图标组件;
	PictureViewToolButton*		m_pOpenFileButton;	//打开文件按钮
	QHBoxLayout*				m_pHLayout;
	QVBoxLayout*				m_pVLayout;
	TitleBar*					m_pTitleBar;
	QString						m_filePath;			//保存获取的图片名称
	BOOL						m_isSvg;
	QPixmap						m_pixPicture;
	BOOL						m_bOpenedFile;
	BOOL						m_bPicPressed;
	Type						m_action;			//动作(放大,缩小,移动...)
	QPoint						m_scaleCenter;		//缩放中心
	FLOAT						m_scaleRatio;		//缩放比率
	QRect						m_paintRect;		//绘制区域
	QPoint						m_xyOffset;			//鼠标移动距离
	QPoint						m_pressedPoint;
};