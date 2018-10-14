#pragma once
#include "stdafx.h"

#define MenuItems QVector<PictureViewMenuItem*>

class PICTUREVIEWKIT_EXPORT PictureViewMenuItem :public QToolButton
{
	Q_OBJECT
public:
	PictureViewMenuItem(QWidget *parent = Q_NULLPTR);
	~PictureViewMenuItem();
	void initMenuItem(QPixmap& icon, QString& text, QString& shortcut);
	bool isHovered() const;

protected:
	void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
	void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
	void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

private:
	QIcon   m_Icon;
	QPixmap m_pixmap;
	QString m_Text;
	QString m_shortcut;
};


class PICTUREVIEWKIT_EXPORT PictureViewPopMenu :public QWidget
{
	Q_OBJECT
public:
	PictureViewPopMenu(QWidget *parent = Q_NULLPTR);
	~PictureViewPopMenu();
	void insertItem(PictureViewMenuItem* item);

protected:
	void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
	MenuItems m_pMuneItems;
	QVBoxLayout* m_pVLayout;
};
