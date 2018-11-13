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
	QLabel*						m_pLogoLabel;       //LOGOͼ�����;
	PictureViewToolButton*		m_pOpenFileButton;	//���ļ���ť
	QHBoxLayout*				m_pHLayout;
	QVBoxLayout*				m_pVLayout;
	TitleBar*					m_pTitleBar;
	QString						m_filePath;			//�����ȡ��ͼƬ����
	BOOL						m_isSvg;
	QPixmap						m_pixPicture;
	BOOL						m_bOpenedFile;
	BOOL						m_bPicPressed;
	Type						m_action;			//����(�Ŵ�,��С,�ƶ�...)
	QPoint						m_scaleCenter;		//��������
	FLOAT						m_scaleRatio;		//���ű���
	QRect						m_paintRect;		//��������
	QPoint						m_xyOffset;			//����ƶ�����
	QPoint						m_pressedPoint;
};