#include "stdafx.h"
#include "pictureviewpopmenu.h"

PictureViewMenuItem::PictureViewMenuItem(QWidget *parent)
	:QToolButton(parent)
{
	setFixedHeight(dpiScaled(25));
	setFixedWidth(dpiScaled(220));
}

PictureViewMenuItem::~PictureViewMenuItem()
{

}

void PictureViewMenuItem::initMenuItem(QPixmap& icon, QString& text, QString& shortcut)
{
	m_pixmap = icon;
	m_Text = text;
	m_shortcut = shortcut;
	m_Icon = QIcon(m_pixmap);
}

void PictureViewMenuItem::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	bool bDown = false, bHover = false, bEnable = false;
	if (isEnabled())
		bEnable = true;

	//	if (isPressed())
	//		bDown = true;
	//
	if (isHovered())
		bHover = true;
	if (bEnable)
	{
		QString strProp;
		//if (bDown)
		//	strProp += "_Down";
		//else 
		if (bHover)
			strProp += "_Hover";
		painter.save();
		painter.setPen(PictureViewDrawHelper::getColorFromTheme("MenuItem" + strProp));
		painter.setBrush(PictureViewDrawHelper::getColorFromTheme("MenuItem" + strProp));
		painter.drawRect(0, 0, this->width(), this->height());
		painter.restore();
	}

	if (!m_Icon.isNull())
	{
		QRect rc(0, 0, dpiScaled(40), dpiScaled(25));
		QSize sz = rc.size() - iconSize();
		rc.adjust(sz.width() / 2, sz.height() / 2, -sz.width() / 2, -sz.height() / 2);
		m_Icon.paint(&painter, rc, Qt::AlignCenter, bEnable ? QIcon::Normal : QIcon::Disabled);
	}

	if (!m_Text.isEmpty())
	{
		painter.save();
		painter.setRenderHint(QPainter::TextAntialiasing, true);
		QTextOption option(Qt::AlignLeft | Qt::AlignVCenter);
		QFont font("Microsoft YaHei", 10);
		painter.setFont(font);
		QRect rc(dpiScaled(40), 0, dpiScaled(110), dpiScaled(25));
		painter.setPen(PictureViewDrawHelper::getColorFromTheme("MenuItem_Text"));
		painter.drawText(rc, m_Text, option);
		painter.restore();
	}

	if (!m_shortcut.isEmpty())
	{
		painter.setRenderHint(QPainter::TextAntialiasing, true);
		QTextOption option(Qt::AlignRight | Qt::AlignVCenter);
		QFont font("Times New Roman", 10);
		painter.setFont(font);
		QRect rc(dpiScaled(135), 0, dpiScaled(70), dpiScaled(25));
		painter.setPen(PictureViewDrawHelper::getColorFromTheme("MenuItem_ShortCut"));
		painter.drawText(rc, m_shortcut, option);
	}
}

void PictureViewMenuItem::mousePressEvent(QMouseEvent *event)
{
	QToolButton::mousePressEvent(event);
}

bool PictureViewMenuItem::isHovered() const
{
	QRect rect = this->rect();
	QPoint pt = mapToGlobal(rect.topLeft());
	QRect rct(pt.x(), pt.y(), rect.width(), rect.height());
	return rct.contains(QCursor::pos());
}


//#用ToolButton拼凑起来的Menu
PictureViewPopMenu::PictureViewPopMenu(QWidget *parent)
	:QWidget(parent)
{
	setWindowFlags(Qt::FramelessWindowHint | Qt::Popup);
	m_pVLayout = new QVBoxLayout(this);
	this->setMouseTracking(true);
	m_pVLayout->setMargin(0);
	m_pVLayout->setSpacing(0);
	setLayout(m_pVLayout);
}

PictureViewPopMenu::~PictureViewPopMenu()
{

}

void PictureViewPopMenu::insertItem(PictureViewMenuItem* pItem)
{
	pItem->installEventFilter(this);
	m_pMuneItems.push_front(pItem);
	m_pVLayout->addWidget(pItem);
}

void PictureViewPopMenu::paintEvent(QPaintEvent *event)
{
	QWidget::paintEvent(event);
}

bool PictureViewPopMenu::eventFilter(QObject* watched, QEvent* event)
{
	if (event->type() == QEvent::MouseButtonRelease)
	{
		this->setVisible(false);
	}

	return QWidget::eventFilter(watched, event);
}
