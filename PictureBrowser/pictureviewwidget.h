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
	void changeShowState(BOOL visible);
	BOOL logoIsVisible();
	void setTitleBar(TitleBar* titlebar);
	void initPictureView();
	void setScaleRatio(float ratio);
	void setScaleCenter(QPoint& pt);
	QRect calculateShowRect();
	BOOL isSvgPicture();

public slots:
	void onOpenPicture();

protected:
	void selectFile();
	void saveFile();
	void closeFile();
	void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
	QLabel*						m_pLogoLabel;               //LOGOͼ��;
	PictureViewToolButton*		m_pOpenFile;				//���ļ���ť
	QHBoxLayout*				m_pHLayout;
	QVBoxLayout*				m_pVLayout;
	QString						m_picturePath;			//�����ȡ��ͼƬ����
	TitleBar*					m_pTitleBar;
	BOOL    m_isSvg;
	QPixmap	m_pixmap;
	//����Ƿ���ͼƬ�ϣ�ͼƬԭʼ�ߴ磬�������ģ����ű�����xyƫ�ƣ�����Ƿ���
	QPoint	m_scaleCenter;
	float   m_scaleRatio;
};