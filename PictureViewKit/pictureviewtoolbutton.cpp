#include "stdafx.h"
#include "pictureviewtoolbutton.h"

PictureViewToolButton::PictureViewToolButton(QWidget *parent) 
	:QPushButton(parent)
{
	m_bPressed = false;
	m_bHovered = false;
}

PictureViewToolButton::~PictureViewToolButton()
{
}

void PictureViewToolButton::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		if (hitButton(event->pos()))
		{
			setDown(true);
			setPressed(true);
		}
		else
		{
			event->ignore();
		}
	}
}

void PictureViewToolButton::mouseReleaseEvent(QMouseEvent *event)
{
	setPressed(false);
	if (!isDown())
		return;
	if (this->rect().contains(event->pos()))
		emit clicked();
	else
		setDown(false);
}

void PictureViewToolButton::paintEvent(QPaintEvent *paintevent)
{
	QPainter painter(this);
	bool bDown = false, bHover = false, bEnable = false;
	if (isEnabled())
		bEnable = true;

	if (isPressed())
		bDown = true;

	if (isHovered())
		bHover = true;
	if (bEnable)
	{
		QString strProp;
		if (bDown)
			strProp += "_Down";
		else if (bHover)
			strProp += "_Hover";

		painter.save();
		painter.setPen(DrawHelper::getColorFromTheme("ToolButton" + strProp));
		painter.setBrush(DrawHelper::getColorFromTheme("ToolButton" + strProp));
		painter.drawRect(0, 0, this->width(), this->height());
		painter.restore();
	}
	QIcon qicon = icon();
	if (!qicon.isNull())
	{
		QRect rc = rect();
		QSize sz = rc.size() - iconSize();
		rc.adjust(sz.width() / 2, sz.height() / 2, -sz.width() / 2, -sz.height() / 2);
		qicon.paint(&painter, rc, Qt::AlignCenter, bEnable ? QIcon::Normal : QIcon::Disabled);
	}
	QString tx = text();
	if (!tx.isEmpty())
	{
		painter.setRenderHint(QPainter::TextAntialiasing, true);
		QTextOption option(Qt::AlignHCenter | Qt::AlignVCenter);
		option.setWrapMode(QTextOption::WordWrap);
		painter.drawText(rect(), tx, option);
	}
}

bool PictureViewToolButton::isPressed() const
{
	return m_bPressed;
}

void PictureViewToolButton::setPressed(bool bPressed)
{
	if (bPressed == m_bPressed)
		return;
	m_bPressed = bPressed;
	update();
}

bool PictureViewToolButton::isHovered() const
{
	QRect rect = this->rect();
	QPoint pt = mapToGlobal(rect.topLeft());
	QRect rct(pt.x(), pt.y(), rect.width(), rect.height());
	return rct.contains(QCursor::pos());
}