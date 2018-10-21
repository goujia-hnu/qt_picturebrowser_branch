#pragma once
#include "application.h"
#include "pictureviewtoolbutton.h"
#include "picturebrowser.h"
#include "pictureviewtitlebar.h"

class PictureViewWidget :public QWidget
{
	Q_OBJECT
public:
	PictureViewWidget(QWidget* parent = Q_NULLPTR);
	~PictureViewWidget();
	void setDrawLogo(BOOL visible);
	BOOL logoVisible();
	void setTitleBar(TitleBar* titlebar);
	void initPictureView();
	void setScaleRatio(float ratio);
	void setScaleCenter(QPoint& pt);
	QRect calculateShowRect();
	BOOL isSvgPicture();

public slots:
	void onOpenPicture();
	void onCloseFile();

protected:
	void selectFile();
	void saveFile();
	void closeFile();
	void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
	QLabel*						m_pLogoLabel;               //LOGO图标;
	PictureViewToolButton*		m_pOpenFile;				//打开文件按钮
	QHBoxLayout*				m_pHLayout;
	QVBoxLayout*				m_pVLayout;
	QString						m_filePath;			//保存获取的图片名称
	TitleBar*					m_pTitleBar;
	BOOL						m_isSvg;
	QPixmap						m_pixPicture;
	//鼠标是否在图片上，图片原始尺寸，缩放中心，缩放比例，xy偏移，鼠标是否按下
	QPoint						m_scaleCenter;
	float						m_scaleRatio;
};